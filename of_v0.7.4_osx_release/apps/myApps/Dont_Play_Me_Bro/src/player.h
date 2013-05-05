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
    
    void setup();
    void update();
    void draw();
    
    float xPos, yPos, wide, tall, xVel, yVel, gravity;
    bool moveUP, moveDOWN, moveLEFT, moveRIGHT;
    
};

#endif /* defined(__Dont_Play_Me_Bro__player__) */
