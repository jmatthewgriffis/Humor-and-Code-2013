//
//  player.cpp
//  Dont_Play_Me_Bro
//
//  Created by J. Matthew Griffis on 5/5/13.
//
//

#include "player.h"

//----------------------------------------------------------------

void player::setup() {
    
    ofNoFill();
    xPos = ofGetWidth()/2;
    yPos = ofGetHeight()/2;
    wide = 50;
    tall = wide;
    xVel = yVel = 10;
    gravity = 0.7;
    
};

//----------------------------------------------------------------

void player::update() {
    
};

//----------------------------------------------------------------

void player::draw() {
    
    /*if (ofDist(ofGetWidth()/2+25, ofGetHeight()/2+25, xPos2, yPos2) < 100) {
        ofFill();
    }
    else ofNoFill();*/
    ofRect(xPos, yPos, wide, tall);
    
};