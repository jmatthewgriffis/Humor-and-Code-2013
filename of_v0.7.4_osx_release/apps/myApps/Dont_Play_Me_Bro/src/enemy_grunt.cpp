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
    
};

//----------------------------------------------------------------

void enemy_grunt::update() {
    
};

//----------------------------------------------------------------

void enemy_grunt::draw() {
    
    ofCircle(xPos, yPos, rad);
    
};