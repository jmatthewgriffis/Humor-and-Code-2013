#pragma once

#include "ofMain.h"
#include "distraction.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int gameState, timer, verticalRez, frameRate, speedy, timeShifts, shiftLength, maxDistractions;
    float timerMax, increasePace;
    bool powerOn;
    ofTrueTypeFont font, fontSmall;
    ofImage iPhone;
    vector<distraction> myDistractions;
    
};
