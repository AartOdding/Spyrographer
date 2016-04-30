// Created by Aart Odding, in April 2016 
// Made with Open Frameworks 0.9.3

#pragma once

#include "ofMain.h"
#include "Gui.h"
#include "Gear.h"

class Path {

public:

	Path();
	~Path();

	void setup(Gui*);
	void update();
	void draw();
	void mousePressed(int, int, int);
	void mouseDragged(int, int, int);
	void erase();
	void finish();
	void startRender();
	void saveRender();

	ofParameter <bool> drawing_mode;

private:

	Gui* gui_pointer;
	Gear gear;

	ofPolyline path;

	bool is_finished = false;
	bool is_rendering = false;
	bool is_rendered = false;

	const float	vertex_spacing = 15.0f;
	const float snapping_distance = 50.0f;
	const int smoothing_size = 3;
	const int steps_per_revolution = 100;

	double total_distance_moved = 0;
	double position_on_path;
	double position_increment;
	double angle_increment;

	// gui elements
	ofxButton start_render_button;
	ofxButton save_render_button;
	ofxButton erase_path_button;
	ofxButton finish_path_button;
};