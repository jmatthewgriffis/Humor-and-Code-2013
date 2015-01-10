//
//  enemy_grunt.h
//  Dont_Play_Me_Bro
//
//  Created by J. Matthew Griffis on 5/5/13.
//
//

#ifndef __Dont_Play_Me_Bro__enemy_grunt__
#define __Dont_Play_Me_Bro__enemy_grunt__

#include "ofMain.h"

class enemy_grunt {
    
public:
    
    void setup(float x, float y);
    void update(float _originX);
    void draw();
    
    float rad, xPos, yPos, xVel, yVel, originX, farOffScreen;
    bool stageRight; // The enemy is offscreen to the left.
    bool pwned; // The enemy is defeated.
    
};

#endif /* defined(__Dont_Play_Me_Bro__enemy_grunt__) */
