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
    yPos = onGround = y-tall/2; // y is ground level so we raise the player appropriately.
    xVel = yVel = 0;
    gravity = 0.3;
    jumpHeight = -10;
    moveUP = moveDOWN = moveLEFT = moveRIGHT = jump = false;
    
};

//----------------------------------------------------------------

void player::update() {
    
    // Gravity is always imposing and modifying a y-velocity on the player, which in turn modify's the player's y-position, but the upward force of the ground cancels out further downward motion:
    yPos += yVel;
    yVel += gravity;
    if (yPos >= onGround) {
        yVel = 0;
        yPos = onGround;
    }
    
    // If a jump is cued, give the player an upward y-velocity and immediately turn off the boolean so the player doesn't fly up forever:
    if (jump) {
        yVel = jumpHeight;
        jump = false;
    }
    
};

//----------------------------------------------------------------

void player::draw() {
    
    ofRect(xPos, yPos, wide, tall);
    
};