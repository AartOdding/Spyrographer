// Created by Aart Odding, in April 2016 
// Made with Open Frameworks 0.9.3

#include "Path.h"


Path::Path() {
	start_render_button.addListener(this, &Path::startRender);
	save_render_button.addListener(this, &Path::saveRender);
	erase_path_button.addListener(this, &Path::erase);
	finish_path_button.addListener(this, &Path::finish);
}


Path::~Path() {
	start_render_button.removeListener(this, &Path::startRender);
	save_render_button.removeListener(this, &Path::saveRender);
	erase_path_button.removeListener(this, &Path::erase);
	finish_path_button.removeListener(this, &Path::finish);
}


void Path::setup(Gui* _gui) {
	gui_pointer = _gui;
	gui_pointer->render_options.add(start_render_button.setup("Start Rendering"));
	gui_pointer->render_options.add(save_render_button.setup("Save Image"));
	gui_pointer->path_options.add(drawing_mode.set("Drawing Tool", true));
	gui_pointer->path_options.add(erase_path_button.setup("Erase Path"));
	gui_pointer->path_options.add(finish_path_button.setup("Finish Path"));
	gear.setup(gui_pointer);
}


void Path::update() {

	if (is_rendering && is_finished) {			// some of the variables are nto yet resetted!!!!!!!!!!!!!!!!!!!!!!!!!!!

		if (total_distance_moved + position_increment < (double)path.getPerimeter() * (double)gear.laps_slider) {	// if not done rendering
			total_distance_moved += position_increment;

			if (path.isClosed()) {
				position_on_path += position_increment;
				if (position_on_path > path.getPerimeter()) position_on_path -= path.getPerimeter();
			} 
			else {
				int times_traversed = total_distance_moved / path.getPerimeter();
				bool moving_forwards = ++times_traversed % 2;

				if (moving_forwards) {
					if (position_on_path + position_increment > path.getPerimeter()) {
						double remainder = (position_on_path + position_increment) - path.getPerimeter();
						position_on_path = path.getPerimeter() - remainder;
					}
					else position_on_path += position_increment;
				}
				else {
					if (position_on_path - position_increment < 0) {
						double remainder = (-1) * (position_on_path - position_increment);
						position_on_path = remainder;
					}
					else position_on_path -= position_increment;
				}
			}

			gear.position = path.getPointAtLength(position_on_path);
			gear.angle += angle_increment;

			for (int i = 0; i < gear.pencils.size(); i++) {
				gear.pencils[i].angle += angle_increment;
				gear.pencils[i].trail.addVertex(gear.pencils[i].getPosition() + gear.position);
			}
		}

		else {
			if (path.isClosed() || (gear.laps_slider % 2 == 0)) {
				for (int i = 0; i < gear.pencils.size(); i++) {
					gear.pencils[i].trail.close();
				}
			}
			is_rendered = true;
			is_rendering = false;
		}
	}
}


void Path::draw() {				// this whole thing can look a lot better
	if (is_finished) {
		ofSetColor(ofColor(20, 100, 20));
		ofSetLineWidth(4); 
	}
	else {
		if (path.getPerimeter() > snapping_distance) {
			if (path[0].squareDistance(path[path.size() - 1]) < pow(snapping_distance, 2)) {
				ofSetColor(ofColor(200, 60, 20));
				ofSetLineWidth(3);
				ofDrawLine(path[0], path[path.size() - 1]);
			}
		}
		ofSetColor(ofColor(0, 0, 0)); 
		ofSetLineWidth(3);
	}
	if (!is_rendered)path.draw();
	if (is_finished) gear.draw(is_rendered);
}


void Path::mousePressed(int x, int y, int button) { 
	gear.mousePressed(x, y, button); 
}


void Path::mouseDragged(int x, int y, int button) {
	if (button == 0 && drawing_mode && !is_finished) path.addVertex(x, y);
	gear.mouseDragged(x, y, button);
}


void Path::finish() {
	if (path.size() > 1) {											// if statement so that pressing finish when there is no path has no effect
		if (path[0].squareDistance(path[path.size() - 1]) < pow(snapping_distance, 2)) path.close();
			
		path = path.getResampledBySpacing(vertex_spacing);			// redo spacing, because smoothing can make vertexes closer together
		
		if (!path.isClosed()) {
			for (int i = 0; i < smoothing_size; i++) {				// insert extra vertexes at ends so the smoothing doesnt move them.
				path.insertVertex(path[0], 0);
				path.insertVertex(path[path.size() - 1], path.size() - 1);
			}
		}
		path = path.getSmoothed(smoothing_size, 1);
	}

	if (path.getPerimeter() < 3 * vertex_spacing) erase();
	else {
		gear.position.set(path[0]);
		gear.deletePencils();
		gear.addPencil();
		drawing_mode = false;
		is_finished = true;
		cout << "Path finished" << endl;
	}
}


void Path::erase() {						// basically a complete reset, only pencils are saved
	path.clear();
	drawing_mode = true;					// turn on drawing again after deleting path
	is_finished = false;					// reset other variables
	is_rendered = false;
	is_rendering = false;
	total_distance_moved = 0;
	position_on_path = 0;
	gear.deleteTrails();
	cout << "Path erased" << endl;
}


void Path::startRender() {
	if (is_finished && gear.pencils.size() > 0 && !is_rendering) {		// check if render is possible
		is_rendering = true;
		is_rendered = false;
		gear.position.set(path[0]);
		position_increment = ((double)path.getPerimeter() * (double)gear.laps_slider) / ((double)gear.revolutions_slider * (double)steps_per_revolution);
		angle_increment = ((double)gear.revolutions_slider * TWO_PI) / ((double)gear.revolutions_slider * (double)steps_per_revolution);
		gear.saveTrails();
		cout << "render started" << endl;
	}
	else cout << "path is not ready to be rendered, or already rendering" << endl;
}


void Path::saveRender() {
	if (is_rendered) {
		ofBackground(ofColor(255, 255, 255));
		draw();
		ofImage render;
		render.grabScreen(0, 0,  ofGetWidth(), ofGetHeight());
		string timeStamp = ofToString(ofGetHours()) + "-" + ofToString(ofGetMinutes()) + "-" + ofToString(ofGetSeconds());
		cout << timeStamp << endl;
		render.save(timeStamp + ".jpg", OF_IMAGE_QUALITY_BEST);
	}
}