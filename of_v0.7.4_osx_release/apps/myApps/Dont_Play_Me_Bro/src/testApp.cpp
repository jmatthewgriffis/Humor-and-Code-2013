#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Housekeeping:
    framerate = 0;
    framerateNormal = 60;
    frameRateSlow = framerateNormal/4;
    ofSetVerticalSync(true);
    ofSetFrameRate(framerateNormal);
    ofSetCircleResolution(60);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    
    // Floats:
    xPosPlayerDefault = ofGetWidth()/2-ofGetWidth()/4;
    originX = originY = 0;
    groundY = ofGetHeight()-100;
    moveSpeed = 7;
    enemyRate = 2; // This many seconds between enemy appearances.
    enemyRateCounter = 0;
    maxEnemies = 10;
    xeno = 0.1; // How quickly an attack closes the distance (bigger = faster).
    mouthX = mouthY = msgX = msgY = textX = textY = 0;
    booYaCounter = 0;
    booYaCounterLimit = 0.5;
    youWonCounter = 0;
    youWonCounterLimit = 10; // Number of seconds the winning message appears.
    
    // Ints:
    storeI = 0;
    enemiesDefeated = 0;
    totalToWin = 50;
    
    // Bools:
    titleScreen = canDisplayMsg1 = canDisplayMsg2 = canDisplayMsg3 = allowAdvance = true;
    moveL = moveR = collided = slow = vanish = rollForSlow = rollForNinja = rollForBooYa = ninjaMsg = booYaMsg = offScreenReset = displayMsg1 = displayMsg2 = displayMsg3 = false;
    
    player.setup(xPosPlayerDefault, groundY);
    
}

//--------------------------------------------------------------
bool bShouldIErase(enemy_grunt & a){
    
    // Zach showed me how to use this method to remove an element from a vector. We create a boolean function, i.e. one that will return a boolean (so we don't use 'void'). We feed it a class and pass a reference label that we make up (in this case 'a') so we can refer to the applicable object. Then we check for a certain condition -- in this case whether the object has moved too far offscreen or been defeated -- and if so we return a boolean value of 'true.' Otherwise it's 'false.'
    
    if (a.stageRight || a.pwned) return true;
    else return false;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (!titleScreen && !displayMsg1 && !displayMsg2 && !displayMsg3) {
        
        // If the player goes offscreen, reset to the default position:
        if (player.xPos < -player.wide || player.xPos > ofGetWidth()+player.wide) {
            player.xPos = xPosPlayerDefault;
            player.yPos = player.onGround;
        }
        
        if (booYaCounter > 0) booYaCounter -= 1/framerate;
        
        if (slow) framerate = frameRateSlow;
        else framerate = framerateNormal;
        ofSetFrameRate(framerate);
        
        if (moveL) originX += moveSpeed; // Translate to the right on LEFT.
        if (moveR) originX -= moveSpeed; // Translate to the left on RIGHT.
        
        // Restore the player to default position where appropriate:
        if (player.yPos == player.onGround && !player.vanish && !player.kickAss){
            if (player.xPos > xPosPlayerDefault) player.xPos--;
            if (player.xPos < xPosPlayerDefault) player.xPos++;
        }
        
        moveR = true;
        // Advance the screen automatically when the player's in the default pos:
        if ((player.xPos != xPosPlayerDefault && player.yPos != player.onGround && !collided) || player.vanish || player.kickAss) moveR = false;
        else if (collided && player.xPos < xPosPlayerDefault/2) moveR = false;
        // ...unless the player attacks:
        //else moveR = false;
        
        // Advance the enemy generation counter once per second:
        if (enemyRateCounter < enemyRate) enemyRateCounter += 1/framerateNormal;
        
        // Generate enemies automatically at the pace we set in setup():
        if (enemyRateCounter >= enemyRate && enemies.size() < maxEnemies) {
            enemy_grunt enemy;
            // Position them just offscreen to the right, taking into account the changing position of the origin:
            enemy.setup(ofGetWidth()+fabs(originX)+100, groundY);
            enemies.push_back(enemy);
            enemyRateCounter = 0;
        }
        
        // Update everyone:
        for (int i = 0; i<enemies.size(); i++) enemies[i].update(originX);
        player.update(framerate);
        
        // Detect a collision between the player and an enemy:
        collided = false; // Set this to false by default, overwritten by collision:
        for (int i=0; i<enemies.size(); i++) {
            
            float enemyDistance = ofDist(player.xPos, player.yPos, enemies[i].xPos+originX, enemies[i].yPos);
            
            float attackDistance = (player.wide/2+enemies[i].rad)*4;
            
            float defeatDistance = player.wide/2+enemies[i].rad;
            
            if (enemyDistance < attackDistance && player.xPos < ofGetWidth()) {
                if (!player.vanish && !player.kickAss) storeI = i; // Record the value of the enemy in question.
                collided = true; // This cues jumping, vanishing, then kicking ass.
                if (enemyDistance < defeatDistance) {
                    enemies[i].pwned = true; // The enemy is defeated.
                    enemiesDefeated++;
                    player.kickAss = false;
                    // Occasionally play a message of condolence:
                    if (rollForBooYa && ofRandom(1) <= 0.6) {
                        booYaMsg = true;
                        booYaCounter = booYaCounterLimit;
                        rollForBooYa = false;
                    }
                    else rollForBooYa = false;
                }
            }
            else player.jump = false;
        }
        rollForBooYa = true;
        if (booYaCounter <= 0) booYaMsg = false;
        
        // Trigger effects on collision:
        if (collided && !player.kickAss) {
            player.jump = true;
            player.tall = 25;
            
            // Randomly activate slow motion:
            if (rollForSlow && ofRandom(1) < 0.2) {
                slow = true;
                rollForSlow = false;
            }
            else rollForSlow = false;
        }
        else { // Restore default values:
            rollForSlow = true;
            slow = false;
            player.tall = 50;
        }
        
        // Randomly comment on the vanishing act:
        if (player.vanish) {
            if (rollForNinja && ofRandom(1) < 0.5) {
                ninjaMsg = true;
                rollForNinja = false;
            }
            else rollForNinja = false;
        }
        else { // Restore default values:
            rollForNinja = true;
            ninjaMsg = false;
        }
        
        // The player reappears at a randomized point:
        if (player.changeX) {
            player.xPos += ofRandom(-xPosPlayerDefault, xPosPlayerDefault);
            player.yPos += ofRandom(-player.yPos, player.onGround-player.yPos-10);
            player.changeX = false;
        }
        
        // We use Xeno's Paradox to "animate" the player's movement toward the enemy's position to make an attack:
        if (player.kickAss) {
            if (player.xPos >= enemies[storeI].xPos+originX) {
                player.xPos -= xeno * ofDist(player.xPos, player.yPos, enemies[storeI].xPos+originX, player.yPos);
            }
            else {
                player.xPos += xeno * ofDist(player.xPos, player.yPos, enemies[storeI].xPos+originX, player.yPos);
            }
            player.yPos += xeno * ofDist(player.xPos, player.yPos, player.xPos, enemies[storeI].yPos);
        }
        
        // Update coordinates for writing messages:
        mouthX = player.xPos-player.wide/2-10;
        mouthY = player.yPos-player.tall/2-10;
        msgX = player.xPos-110;
        msgY = ofGetHeight()/2+10;
        textX = player.xPos-140;
        textY = ofGetHeight()/2;
        
        // Following up the boolean function we created above, this oF function sorts the vector according to the values of the booleans and then removes any with a 'true' value:
        ofRemove(enemies,bShouldIErase);
        
        // If the player defeats all the enemies, cue the win screen, then restart the game:
        if (enemiesDefeated >= totalToWin) youWonCounter += 1/framerate;
        if (youWonCounter >= youWonCounterLimit) setup();
        
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    
    if (titleScreen) {
        
        // Draw the title:
        ofDrawBitmapString(" -- Don't Play Me, Bro! --\n\n\n\n\n\na game by J. Matthew Griffis\n\n\n\n\n\n  Press [SPACE] to start.", ofGetWidth()/2-100, ofGetHeight()/2-75);
        
        // Draw the copyright:
        ofDrawBitmapString("(c) 2013 J. Matthew Griffis", ofGetWidth()/2-100, ofGetHeight()-25);
        
    }
    
    // The message screens:
    else if (displayMsg1 || displayMsg2 || displayMsg3) {
        
        // Draw the player at a larger scale in fixed position:
        ofRect(ofGetWidth()/2+200, ofGetHeight()/2+200, 100, 100);
        // Connect the player and the message:
        ofLine(ofGetWidth()/2+125, ofGetHeight()/2+150, ofGetWidth()/2+25, ofGetHeight()/2+70);
        
        // Draw the message:
        
        if (displayMsg1) {
            canDisplayMsg1 = false;
            ofDrawBitmapString("Whoa there, bro. Whoa.\n\nI see what you're doing, bro. You\nsee what's up and you want to help.\nHey, I appreciate it, bro.\n\nBut don't worry -- I got this!\nJust hit [SPACE], sit back and\nlet me show you how it's done.", ofGetWidth()/2-230, ofGetHeight()/2-60);
        }
        
        else if (displayMsg2) {
            canDisplayMsg2 = false;
            ofDrawBitmapString("Now bro, I admire your enthusiasm.\nI really do. That's why we're bros, bro!\n\nBut let's be honest here.\nWe both know your 'helping'\nwill only interfere, bro.\n\nI'm doing some cool stuff, right bro?\nDo you know how to do that stuff?\n\nBro. You do not.\n\nLet's just forget about this, hit [SPACE],\nand you can cheer me on, bro!\nI can't do it without you!", ofGetWidth()/2-230, ofGetHeight()/2-125);
        }
        
        else if (displayMsg3) {
            canDisplayMsg3 = false;
            ofDrawBitmapString("Bro! FOR SERIOUS, BRO.\nKNOCK IT OFF.\n\nI'm not sure you're listening.\nThis action is too complex for you,\na'ight bro?\n\nI'm just trying to make it easier\non you so you can have more fun.\nDon't you see that, bro?\nLet me take care of things\nand we'll all have a good time;\notherwise it's challenge,\nfrustration and anger, bro.\n\nNow, I need you to press [SPACE], and\nthen everything will be chill, bro.", ofGetWidth()/2-230, ofGetHeight()/2-175);
        }
        
    }
    
    // The game screen:
    else {
        
        if (youWonCounter == 0) { // If the player hasn't won the game:
            
            // Draw the ground:
            ofLine(0, groundY, ofGetWidth(), groundY);
            
            // Draw messages:
            if (slow || ninjaMsg || booYaMsg) {
                string string;
                ofLine(mouthX, mouthY, msgX, msgY); // Line to "speech bubble."
                if (slow) string = "I do it slow, bro!"; // Write a message if there's slow motion.
                if (ninjaMsg) string = "Poof! Like a ninja, bro!"; // Write a message sometimes upon vanishing.
                if (booYaMsg) string = "Booya, bro!"; // Write a message sometimes upon defeating enemy.
                ofDrawBitmapString(string, textX, textY);
            }
            
            // Indicate the number of Bro Points:
            ofDrawBitmapString("Bro Points: MAXED OUT!", 25, 25);
            
            // Describe the controls:
            ofDrawBitmapString("CONTROLS:\n[A]/[D] or [LEFT]/[RIGHT] to move.\n[SPACE] to jump.\n[SPACE] while jumping to attack.\n[R] to restart if things get crazy.", 25, ofGetHeight()-70);
            
            // Describe the goal:
            ofDrawBitmapString("Help Square defeat all the circles in\norder to unleash the Ultimate Attack.\n\nOnce the Attack completes, the\ngame restarts, so watch closely!", ofGetWidth()-350, ofGetHeight()-70);
            
            // Keep an onscreen count of enemies defeated and progress towards goal:
            ofDrawBitmapString("Vicious circles defeated: " + ofToString(enemiesDefeated) + " / " + ofToString(totalToWin), ofGetWidth()-290, 25);
            
            // The player stays in one place and everything else translates as the player "moves":
            ofPushMatrix();
            ofTranslate(originX, originY);
            for (int i=0; i<enemies.size(); i++) enemies[i].draw();
            ofPopMatrix();
            
            // Debug - draw a line from the center of each enemy to just above the player:
            /*for (int i=0; i<enemies.size(); i++) {
             ofLine(player.xPos, player.yPos-200, enemies[i].xPos+originX, enemies[i].yPos);
             }*/
            
            player.draw();
            
        }
        
        // The end screen:
        else {
            
            // Draw some messages:
            ofDrawBitmapString("-- ERROR: ULTIMATE ATTACK DOES NOT EXIST. --", ofGetWidth()/2-160, ofGetHeight()/2-100);
            
            ofDrawBitmapString("I played you, bro!\n\n   HA! HA! HA!\n   So funny!\n   Square out.", ofGetWidth()/2-75, ofGetHeight()/2);
            // Draw the player at a larger scale in fixed position:
            ofRect(ofGetWidth()/2+200, ofGetHeight()/2+200, 100, 100);
            // Connect the player and the message:
            ofLine(ofGetWidth()/2+125, ofGetHeight()/2+150, ofGetWidth()/2+25, ofGetHeight()/2+70);
            
        }
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    // Enable movement on keyPress:
    switch (key) {
            
            // Debug - generate an enemy on command:
            /*case 'm':
             enemy_grunt enemy;
             enemy.setup(ofGetWidth()/2+300*enemies.size(), groundY);
             enemies.push_back(enemy);
             break;*/
            
            // Trigger/advance messages where appropriate:
        case 'a':
        case 'A':
        case OF_KEY_LEFT:
        case 'd':
        case 'D':
        case OF_KEY_RIGHT:
        case ' ':
            if (allowAdvance) {
                if (titleScreen) titleScreen = false;
                else if (canDisplayMsg1) displayMsg1 = true;
                else if (displayMsg1) displayMsg1 = false;
                else if (canDisplayMsg2) displayMsg2 = true;
                else if (displayMsg2) displayMsg2 = false;
                else if (canDisplayMsg3) displayMsg3 = true;
                else if (displayMsg3) displayMsg3 = false;
            }
            allowAdvance = false; // This prevents advancing by holding the key.
            break;
            
            // Restart the game:
        case 'r':
            // Clear out the vector:
            for (int i=0; i<enemies.size(); i++) enemies.erase(enemies.begin(), enemies.end());
            setup(); // Reload from the top.
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    // Disable movement on keyRelease:
    switch (key) {
        case 'a':
        case 'A':
        case OF_KEY_LEFT:
        case 'd':
        case 'D':
        case OF_KEY_RIGHT:
        case ' ':
            allowAdvance = true;
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}