//
//  distraction.cpp
//  This_Connected_Life
//
//  Created by J. Matthew Griffis on 5/11/13.
//
//

#include "ofMain.h"
#include "distraction.h"

//--------------------------------------------------------------
void distraction::setup(float x, float y) {
    
    xPos = x;
    yPos = y;
    xVel = yVel = 5;
    wide = 50;
    tall = wide;
    marginH = 30; // Distance from sides of window to sides of iPhone screen.
    marginV = 105; // Distance from top/bottom of window to top/bottom of iPhone screen.
    
}

//--------------------------------------------------------------
void distraction::update() {
    
    xPos += xVel;
    yPos += yVel;
    
    // Reverse direction upon hitting an edge:
    if (xPos - wide/2 < marginH || xPos + wide/2 > ofGetWidth()-marginH) xVel *= -1;
    if (yPos - tall/2 < marginV || yPos + tall/2 > ofGetHeight()-marginV) yVel *= -1;
    
}

//--------------------------------------------------------------
void distraction::draw() {
    
    ofSetColor(0, 0, 255);
    ofRect(xPos, yPos, wide, tall);
    ofSetColor(255);
    
}