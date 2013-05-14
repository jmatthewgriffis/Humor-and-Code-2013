#pragma once

#include "ofMain.h"
#include "player.h"
#include "enemy_grunt.h"

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
    
    float framerate, framerateNormal, frameRateSlow, xPosPlayerDefault, originX, originY, groundY, moveSpeed, enemyRate, enemyRateCounter, maxEnemies, xeno, mouthX, mouthY, msgX, msgY, textX, textY, booYaCounter, booYaCounterLimit, youWonCounter, youWonCounterLimit, dontPlayMeMsgCounter, dontPlayMeMsgCounterLimit;
    int storeI; // Store a specific value of i for a vector.
    int enemiesDefeated, totalToWin;
    bool titleScreen, moveL, moveR, collided, slow, vanish, rollForSlow, rollForNinja, rollForBooYa, ninjaMsg, booYaMsg, offScreenReset, canDisplayMsg1, displayMsg1, canDisplayMsg2, displayMsg2, canDisplayMsg3, displayMsg3, allowAdvance, dontPlayMeMsg, pickMsg;
    
    ofTrueTypeFont gameFontBig, gameFontSmall, helv;
    player player;
    vector<enemy_grunt> enemies; // Make a dynamic array for enemy objects...
    
};
