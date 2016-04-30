// Created by Aart Odding, in April 2016 
// Made with Open Frameworks 0.9.3

#pragma once

#include "ofMain.h"
#include "ofxGui.h"



class Gui {

public:

	Gui();
	~Gui();

	void draw();
	ofVec2f getPosition();
	ofVec2f getDimensions();

	ofxGuiGroup render_options;
	ofxGuiGroup path_options;			// these have to be public, so parameters can be added from ofapp
	ofxGuiGroup gear_options;
	ofxGuiGroup color_options;

private:

	ofxPanel gui_panel;

};