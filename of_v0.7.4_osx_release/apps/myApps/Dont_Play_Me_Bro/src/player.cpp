//
//  player.cpp
//  Dont_Play_Me_Bro
//
//  Created by J. Matthew Griffis on 5/5/13.
//
//

#include "player.h"

//----------------------------------------------------------------

void player::setup(float x, float y) {
    
    wide = 50;
    tall = wide; // Make a square.
    xPos = x;
    yPos = y-tall/2; // y is ground level so we raise the player appropriately.
    xVel = yVel = 0;
    gravity = 0;
    
};

//----------------------------------------------------------------

void player::update() {
    
};

//----------------------------------------------------------------

void player::draw() {
    
    ofRect(xPos, yPos, wide, tall);
    
};