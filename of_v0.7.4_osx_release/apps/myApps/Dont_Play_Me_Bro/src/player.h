//
//  player.h
//  Dont_Play_Me_Bro
//
//  Created by J. Matthew Griffis on 5/5/13.
//
//

#ifndef __Dont_Play_Me_Bro__player__
#define __Dont_Play_Me_Bro__player__

#include "ofMain.h"

class player {
    
public:
    
    void setup(float x, float y);
    void update();
    void draw();
    
    float wide, tall, xPos, yPos, onGround, xVel, yVel, gravity, jumpHeight;
    bool moveUP, moveDOWN, moveLEFT, moveRIGHT, allowJump, jump, topOfJump, vanish;
    
};

#endif /* defined(__Dont_Play_Me_Bro__player__) */
