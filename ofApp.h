// Created by Aart Odding, in April 2016 
// Made with Open Frameworks 0.9.3

#pragma once

#include "ofMain.h"
#include "Gui.h"
#include "Path.h"


class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();

	void mousePressed(int, int, int);
	void mouseDragged(int, int, int);

private:
	
	Gui myGui;
	Path myPath;

	ofImage pencil_front;
	ofImage pencil_back;
};
