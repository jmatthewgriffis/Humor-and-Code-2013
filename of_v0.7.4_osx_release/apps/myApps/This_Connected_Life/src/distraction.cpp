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
void distraction::setup(float x, float y, int v) {
    
    color.r = 0;
    color.g = 0;
    color.b = 255;
    xPos = x;
    yPos = y;
    
    // Randomize the direction of velocity:
    if (ofRandom(1) >= 0.5) xVel = v;
    else xVel = -v;
    if (ofRandom(1) > 0.5) yVel = v;
    else yVel = -v;
    
    wide = 50;
    tall = wide;
    marginH = 30; // Distance from sides of window to sides of iPhone screen.
    marginV = 105; // Distance from top/bottom of window to top/bottom of iPhone screen.
    collided = destroyMe = false;
    
    distractionPic.loadImage("distraction.jpg"); // http://1.bp.blogspot.com/-2fjLrL8Wcj8/Thgw_1H9XyI/AAAAAAAAAPA/MSmmxizJutU/s1600/Distraction.jpg
    
}

//--------------------------------------------------------------
void distraction::update() {
    
    // Take action upon collision:
    if (collided) color.r = 255;
    else color.r = 0;
    
    // If not colliding, turn off the variable:
    collided = false;
    
    xPos += xVel;
    yPos += yVel;
    
    // Prevent the object from moving out of bounds:
    if (xPos - wide/2 < marginH) xPos = marginH + wide/2;
    if (xPos + wide/2 > ofGetWidth()-marginH) xPos = ofGetWidth()-marginH - wide/2;
    if (yPos - tall/2 < marginV) yPos = marginV + tall/2;        
    if (yPos + tall/2 > ofGetHeight()-marginV) yPos = ofGetHeight()-marginV - tall/2;
    
    // Reverse direction upon hitting an edge:
    if (xPos - wide/2 == marginH || xPos + wide/2 == ofGetWidth()-marginH) xVel *= -1;
    if (yPos - tall/2 == marginV || yPos + tall/2 == ofGetHeight()-marginV) yVel *= -1;
    
}

//--------------------------------------------------------------
void distraction::draw() {
    
    //ofSetColor(color);
    ofSetColor(255);
    //ofRect(xPos, yPos, wide, tall);
    distractionPic.draw(xPos, yPos, wide, tall);
    //ofSetColor(255);
    
}