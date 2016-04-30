// Created by Aart Odding, in April 2016 
// Made with Open Frameworks 0.9.3

#pragma once

#include "ofMain.h"

struct Pencil {

	const int radius = 10;

	double angle = ofRandom(0.0f, TWO_PI);
	double length = ofRandom(35.0f, 120.0f);

	ofColor color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
	ofPolyline trail;

	void draw() {
		ofSetColor(color);
		ofDrawCircle(getPosition(), radius);
	}

	void drawTrail() {
		ofSetColor(color);
		ofSetLineWidth(3);
		trail.draw();
	}

	void drawConnection(float _gear_radius) {
		ofVec2f temp_pos = ofVec2f(0.6 * _gear_radius * cos(angle), 0.6 * _gear_radius * sin(angle));
		ofSetLineWidth(3);
		ofSetColor(ofColor(0));
		ofDrawLine(getPosition(), temp_pos);
	}

	ofVec2f getPosition() { 
		return ofVec2f(length * cos(angle), length * sin(angle)); 
	}

	bool overlaps(ofVec2f& pos) { 
		return getPosition().distanceSquared(pos) < pow(radius, 2); 
	}
};