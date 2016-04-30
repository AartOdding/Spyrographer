// Created by Aart Odding, in April 2016 
// Made with Open Frameworks 0.9.3

#pragma once

#include "Gui.h"
#include "Pencil.h"


class Gear {
	
public:

	Gear();
	~Gear();

	void setup(Gui*);
	void draw(bool);
	void mousePressed(int, int, int);
	void mouseDragged(int, int, int);
	void saveTrails();
	void deleteTrails();
	void colorChanged(int&);

	void addPencil();
	void removePencil();
	void deletePencils() { if (pencils.size() > 0) pencils.clear(); }
	
	ofVec2f position;
	double angle = 0;
	vector <Pencil> pencils;
	ofxSlider <int> revolutions_slider;
	ofxSlider <int> laps_slider;

private:

	Gui* gui_pointer = nullptr;
	Pencil* active_pencil = nullptr;

	ofImage gear_image;

	const float radius = 30;

	// gui elements
	ofxButton add_pencil_button;
	ofxButton remove_pencil_button;
	ofxSlider <int> red_slider;
	ofxSlider <int> green_slider;
	ofxSlider <int> blue_slider;

};