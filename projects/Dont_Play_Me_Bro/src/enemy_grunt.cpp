//
//  enemy_grunt.cpp
//  Dont_Play_Me_Bro
//
//  Created by J. Matthew Griffis on 5/5/13.
//
//

#include "enemy_grunt.h"

//----------------------------------------------------------------

void enemy_grunt::setup(float x, float y) {
    
    rad = 25;
    xPos = x;
    yPos = y-rad; // y is ground level so we raise the grunt appropriately.
    xVel = yVel = 0;
    originX = 0;
    farOffScreen = -300;
    stageRight = pwned = false;
    
};

//----------------------------------------------------------------

void enemy_grunt::update(float _originX) {
    
    originX = _originX;
    if (xPos - fabs(originX) < farOffScreen) stageRight = true;
    
};

//----------------------------------------------------------------

void enemy_grunt::draw() {
    
    ofCircle(xPos, yPos, rad);
    
};