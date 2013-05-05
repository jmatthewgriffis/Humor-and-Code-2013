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
    
    void setup();
    void update();
    void draw();
    
    float xPos, yPos, rad, xVel, yVel;
    
};

#endif /* defined(__Dont_Play_Me_Bro__enemy_grunt__) */
