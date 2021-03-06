//
//  distraction.h
//  This_Connected_Life
//
//  Created by J. Matthew Griffis on 5/11/13.
//
//

#ifndef __This_Connected_Life__distraction__
#define __This_Connected_Life__distraction__

class distraction {
    
public:
    
    void setup(float x, float y, int v);
    void update();
    void draw();
    
    ofColor color;
    ofImage distractionPic;
    float xPos, yPos;
    int wide, tall, xVel, yVel, marginH, marginV;
    bool collided, destroyMe;
    
};

#endif /* defined(__This_Connected_Life__distraction__) */
