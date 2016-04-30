// Created by Aart Odding, in April 2016 
// Made with Open Frameworks 0.9.3

#include "gear.h"


Gear::Gear() {
	add_pencil_button.addListener(this, &Gear::addPencil);
	remove_pencil_button.addListener(this, &Gear::removePencil);
	red_slider.addListener(this, &Gear::colorChanged);
	green_slider.addListener(this, &Gear::colorChanged);
	blue_slider.addListener(this, &Gear::colorChanged);
	gear_image.load("gearIcon.PNG");
}
 

Gear::~Gear() {
	add_pencil_button.removeListener(this, &Gear::addPencil);
	remove_pencil_button.removeListener(this, &Gear::removePencil);
	red_slider.removeListener(this, &Gear::colorChanged);
	green_slider.removeListener(this, &Gear::colorChanged);
	blue_slider.removeListener(this, &Gear::colorChanged);
}


void Gear::setup(Gui* _gui) {
	gui_pointer = _gui;
	gui_pointer->gear_options.add(add_pencil_button.setup("Add Pencil"));
	gui_pointer->gear_options.add(remove_pencil_button.setup("Remove Pencil"));
	gui_pointer->gear_options.add(revolutions_slider.setup("Revolutions", 17, 1, 50));
	gui_pointer->gear_options.add(laps_slider.setup("Laps", 4, 1, 20));
	gui_pointer->color_options.add(red_slider.setup("Red", 127, 0, 255));
	gui_pointer->color_options.add(green_slider.setup("Green", 127, 0, 255));
	gui_pointer->color_options.add(blue_slider.setup("Blue", 127, 0, 255));
}


void Gear::draw(bool _completed) {
	if (!_completed) {
		ofPushMatrix();
		ofTranslate(position.x, position.y);

		for (auto pen : pencils) {						// draw line from gear to pencil
			pen.drawConnection(radius);
		}

		ofPushMatrix();
		ofRotate(ofRadToDeg(angle));
		ofSetColor(ofColor(200));
		gear_image.draw(-radius, -radius, 2 * radius, 2 * radius);
		ofPopMatrix();

		for (auto pen : pencils) {
			pen.draw();
		}
		ofPopMatrix();
	}

	for (auto pen : pencils) {
		pen.drawTrail();
	}
}


void Gear::mousePressed(int x, int y, int button) {
	for (int i = pencils.size() - 1; i >= 0; i--) {
		if (pencils[i].overlaps(ofVec2f(x, y) - position)) {
			active_pencil = &pencils[i];
			ofColor temp_color = ofColor(pencils[i].color);
			red_slider = temp_color.r;
			green_slider = temp_color.g;
			blue_slider = temp_color.b;
			return;
		}
	}
	//active_pencil = nullptr;
}


void Gear::mouseDragged(int x, int y, int button) {
	if (active_pencil) {
		ofVec2f rel_position = ofVec2f(x, y) - position;
		active_pencil->length = rel_position.length();
		if (rel_position.x >= 0) active_pencil->angle = atan(rel_position.y / rel_position.x);
		else active_pencil->angle = atan(rel_position.y / rel_position.x) + PI;
	}
}


void Gear::colorChanged(int&) {
	red_slider.setFillColor(ofColor(red_slider, 0, 0));
	green_slider.setFillColor(ofColor(0, green_slider, 0));
	blue_slider.setFillColor(ofColor(0, 0, blue_slider));
	if (active_pencil) {
		active_pencil->color = ofColor(red_slider, green_slider, blue_slider);
	}
}


void Gear::saveTrails() {
	for (int i = 0; i < pencils.size(); i++) {
		pencils[i].trail.addVertex(position + pencils[i].getPosition());
	}
}


void Gear::deleteTrails() {
	for (int i = 0; i < pencils.size(); i++) {
		pencils[i].trail.clear();
	}
}


void Gear::addPencil() {
	pencils.push_back(Pencil());
	active_pencil = &pencils.back();		// fucked up place ??? fix color not being resetted
	ofColor temp_color = ofColor(pencils.back().color);
	red_slider = temp_color.r;
	green_slider = temp_color.g;
	blue_slider = temp_color.b;
}


void Gear::removePencil() { 
	if (pencils.size() > 0) pencils.pop_back();		// remove the proper pencil
}