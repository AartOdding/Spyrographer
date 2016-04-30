// Created by Aart Odding, in April 2016 
// Made with Open Frameworks 0.9.3

#include "Gui.h"

Gui::Gui() {
	gui_panel.setup("Options");
	gui_panel.add(render_options.setup("Render"));
	gui_panel.add(path_options.setup("Path"));
	gui_panel.add(gear_options.setup("Gear"));
	gui_panel.add(color_options.setup("Color"));
}


Gui::~Gui() {
}


void Gui::draw() {
	ofSetColor(ofColor(0));				// draw a line at the top of the screen
	ofSetLineWidth(1);
	ofDrawLine(0, 0, ofGetWidth(), 0);

	gui_panel.draw();
}


ofVec2f Gui::getPosition() {
	return gui_panel.getPosition();
}


ofVec2f Gui::getDimensions() {
	return ofVec2f(gui_panel.getWidth(), gui_panel.getHeight());
}