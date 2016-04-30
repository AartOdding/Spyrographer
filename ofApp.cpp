// Created by Aart Odding, in April 2016 
// Made with Open Frameworks 0.9.3

#include "ofApp.h"


void ofApp::setup() {
	ofSetFullscreen(true);
	ofSetFrameRate(60);
	myPath.setup(&myGui);
	pencil_front.load("pencil_front.PNG");
	pencil_back.load("pencil_back.PNG");
}


void ofApp::update() {
	myPath.update();
}


void ofApp::draw() {
	ofBackground(255);
	myPath.draw();
	myGui.draw();
	
	bool inside_gui = false;
	if (ofGetMouseX() > myGui.getPosition().x && ofGetMouseY() > myGui.getPosition().y) {
		if (ofGetMouseX() < myGui.getPosition().x + myGui.getDimensions().x && ofGetMouseY() < myGui.getPosition().y + myGui.getDimensions().y) {
			inside_gui = true;
		}
	}

	if (myPath.drawing_mode && !inside_gui) {
		ofHideCursor();
		ofSetColor(ofColor(255));
		pencil_back.draw(ofGetMouseX(), ofGetMouseY() - 40, 40, 40);
		ofSetColor(ofColor(0));
		pencil_front.draw(ofGetMouseX(), ofGetMouseY() - 40, 40, 40);
	}
	else ofShowCursor();
}


void ofApp::mousePressed(int x, int y, int button) {
	myPath.mousePressed(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button) {
	myPath.mouseDragged(x, y, button);
}