//
//  enemy_grunt.cpp
//  Dont_Play_Me_Bro
//
//  Created by J. Matthew Griffis on 5/5/13.
//
//

#include "enemy_grunt.h"

//----------------------------------------------------------------

void enemy_grunt::setup() {
    
    xPos = ofGetWidth()/2-100;
    yPos = ofGetHeight()/2+25;
    rad = 25;
    
};

//----------------------------------------------------------------

void enemy_grunt::update() {
    
};

//----------------------------------------------------------------

void enemy_grunt::draw() {
    
    ofCircle(xPos, yPos, rad);
    
};