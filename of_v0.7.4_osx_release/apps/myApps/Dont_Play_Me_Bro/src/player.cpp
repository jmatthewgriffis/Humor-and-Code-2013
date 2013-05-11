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
    vanishCounter = 0;
    vanishLimit = 1;
    framerate = 0;
    yVelTiny = 0.25;
    moveUP = moveDOWN = moveLEFT = moveRIGHT = allowJump = jump = topOfJump = vanish = false;
    
};

//----------------------------------------------------------------

void player::update(float _framerate) {
    
    framerate = _framerate;
    
    topOfJump = false;
    
    // Disappear for a certain duration and then reappear:
    if (vanish) vanishCounter += 1/framerate;
    if (vanishCounter >= vanishLimit) {
        vanish = false;
        yVel = yVelTiny;
        vanishCounter = 0;
    }
    
    // Keep the player from falling through the ground:
    if (yPos >= onGround) {
        yVel = 0;
        yPos = onGround;
    }
    
    if (yPos == onGround) allowJump = true;
    else allowJump = false;
    
    // If a jump is cued, give the player an upward y-velocity and immediately turn off the boolean so the player doesn't fly up forever:
    if (jump && allowJump) {
        yVel = jumpHeight;
        jump = false;
    }
    
    // If the player's not on the ground (and therefore has a yVel), check if near the top of the jump:
    if (yPos < onGround && fabs(yVel) < yVelTiny) topOfJump = true;
    
    if (topOfJump) vanish = true; // Make like a ninja.
    else {
        // Unless the player is making like a ninja, gravity is always imposing and modifying a y-velocity, which in turn modifies the player's y-position:
        yPos += yVel;
        yVel += gravity;
    }
    
};

//----------------------------------------------------------------

void player::draw() {
    
    if (!vanish) ofRect(xPos, yPos, wide, tall);
    
};