#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    frameRate = 60;
    
    // Housekeeping:
    ofSetVerticalSync(true);
    ofSetCircleResolution(60);
    ofSetFrameRate(frameRate);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofEnableAlphaBlending();
    //ofSetDataPathRoot("data/"); // This is necessary to make a standalone app.
    
    // ints:
    gameState = 0;
    timer = 0;
    verticalRez = 768;
    speedy = 1;
    timeShifts = 10;
    shiftLength = 10;
    maxDistractions = 150;
    frameCount = 0;
    aVel = 1;
    
    // floats:
    timerMax = 2*frameRate;
    increasePace = 0.9;
    
    // bools:
    powerOn = true;
    chaos = false;
    
    // images:
    iPhone.loadImage("iphone.jpg");
    
    // fonts:
    font.loadFont("helvetica.otf", 18);
    fontSmall.loadFont("helvetica.otf", 12);
    
    // colors;
    powerButton.r = 255;
    powerButton.g = 0;
    powerButton.b = 0;
    powerButton.a = 1;
    
}

//--------------------------------------------------------------
bool bShouldIErase(distraction & a){
    
    // Zach showed me how to use this method to remove an element from a vector. We create a boolean function, i.e. one that will return a boolean (so we don't use 'void'). We feed it a class and pass a reference label that we make up (in this case 'a') so we can refer to the applicable object. Then we check for a certain condition and if so we return a boolean value of 'true.' Otherwise it's 'false.'
    
    if (a.destroyMe) return true;
    else return false;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (gameState == 1) {
        
        if (powerOn) {
            
            if (myDistractions.size() > 15) {
            // Draw attention to the power button by fading it in and out:
            powerButton.a += aVel;
            if (powerButton.a >= 255 || powerButton.a <= 0) aVel *= -1;
            }
            else {
                powerButton.a = 0;
                aVel = 1;
            }
            
            frameCount++;
            
            if (!chaos && myDistractions.size() == 0 && frameCount > frameRate) {
                distraction distraction;
                distraction.setup(ofGetWidth()/2, ofGetHeight()/2, 1);
                myDistractions.push_back(distraction);
            }
            
            if (chaos) {
                // Generate distractions at a set pace with randomized positioning:
                if (timer < timerMax) timer ++;
                else if (timer >= timerMax && myDistractions.size() < maxDistractions) {
                    distraction distraction;
                    distraction.setup(ofRandom(distraction.wide, ofGetWidth()-distraction.wide), ofRandom(distraction.tall, ofGetHeight()-distraction.tall), speedy);
                    myDistractions.push_back(distraction);
                    timer = 0;
                }
                
                // Change the distractions' speed based on duration of game:
                for (int i = 0; i < timeShifts; i++) {
                    if (frameCount > frameRate * shiftLength * i) {
                        if (i < 5) speedy = 1 + i;
                        timerMax = 2 * frameRate * powf(increasePace, i);
                    }
                }
            }
            
            // Collision detection between distractions:
            for (int i=0; i<myDistractions.size(); i++) {
                
                myDistractions[i].update();
                
                for (int j=i+1; j<myDistractions.size(); j++) {
                    if (myDistractions[i].xPos-myDistractions[i].wide/2 <= myDistractions[j].xPos+myDistractions[j].wide/2 && myDistractions[i].xPos+myDistractions[i].wide/2 > myDistractions[j].xPos-myDistractions[j].wide/2 && myDistractions[i].yPos-myDistractions[i].tall/2 <= myDistractions[j].yPos+myDistractions[j].tall/2 && myDistractions[i].yPos+myDistractions[i].tall/2 > myDistractions[j].yPos-myDistractions[j].tall/2) {
                        
                        // If the velocities are in the same direction, do nothing:
                        // xVel
                        if ((myDistractions[i].xVel >= 0 && myDistractions[j].xVel >= 0) || (myDistractions[i].xVel < 0 && myDistractions[j].xVel < 0)) {}
                        else { // Otherwise, reverse:
                            myDistractions[i].xVel *= -1;
                            myDistractions[j].xVel *= -1;
                        }
                        // yVel
                        if ((myDistractions[i].yVel >= 0 && myDistractions[j].yVel >= 0) || (myDistractions[i].yVel < 0 && myDistractions[j].yVel < 0)) {}
                        else { // Otherwise, reverse:
                            myDistractions[i].yVel *= -1;
                            myDistractions[j].yVel *= -1;
                        }
                        
                        myDistractions[i].collided = true;
                        myDistractions[j].collided = true;
                        
                    }
                }
            }
            
            // Following up the boolean function we created above, this oF function sorts the vector according to the values of the booleans and then removes any with a 'true' value:
            ofRemove(myDistractions,bShouldIErase);
            
        } // End if (powerOn).
        
    } // End gameState = 1.
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // Draw the image proportionately based on varying the height:
    iPhone.draw(ofGetWidth()/2, ofGetHeight()/2, iPhone.getWidth()*(verticalRez/iPhone.getHeight()), verticalRez);
    
    // Draw a rect to cover the contents of the phone's screen:
    ofSetColor(255);
    if (!powerOn) ofSetColor(0);
    ofRect(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()-65, ofGetHeight()-210);
    ofSetColor(255);
    
    if (gameState == 0) {
        
        // Draw the title screen:
        
        ofSetColor(0);
        
        ofPushMatrix();
        ofTranslate(0, -100);
        font.drawString("Sweet, new phone!", ofGetWidth()/2-108, ofGetHeight()/2);
        font.drawString("Let's start using it.", ofGetWidth()/2-108, ofGetHeight()/2 + 100);
        ofSetColor(200);
        ofRect(ofGetWidth()/2-12, ofGetHeight()/2+142, 50, 35);
        ofSetColor(255);
        font.drawString("OK", ofGetWidth()/2-30, ofGetHeight()/2 + 150);
        ofPopMatrix();
        
        ofSetColor(0);
        fontSmall.drawString("This Connected Life ---------------------------\n------- Copyright 2013 J. Matthew Griffis", ofGetWidth()/2-150, ofGetHeight()-127);
        ofSetColor(255);
        
    }
    
    if (gameState == 1) {
        
        if (powerOn) {
            
            ofSetColor(0);
            if (!chaos) {
                font.drawString("The first thing we\n have to learn is", ofGetWidth()/2-110, ofGetHeight()/2-200);
                if (myDistractions.size() > 0) {
                    if (frameCount > 120) {
                        font.drawString("...oh, dear.", ofGetWidth()/2-50, ofGetHeight()/2-100);
                    }
                    if (frameCount > 210) {
                        font.drawString("Well, just click on it\nto make it go away.", ofGetWidth()/2-125, ofGetHeight()/2);
                    }
                }
            }
            else {
                
                if (myDistractions.size() < 5) {
                    font.drawString("       Great.\nNow we can proceed\nto the most important\n    principles of", ofGetWidth()/2-120, ofGetHeight()/2+50);
                }
                if (myDistractions.size() < 10) {
                    
                    if (myDistractions.size() > 1) {
                        font.drawString("Umm...", ofGetWidth()/2-5, ofGetHeight()/2+200);
                    }
                    if (myDistractions.size() > 3) {
                        font.drawString("Yikes.", ofGetWidth()/2-55, ofGetHeight()/2+250);
                    }
                    
                }
                
            }
            ofSetColor(255);
            
            // Draw those infernal distractions:
            for (int i=0; i<myDistractions.size(); i++) myDistractions[i].draw();
            
        } // End if (powerOn).
        
    } // End gameState = 1.
    
    // Draw a rect over the power button:
    ofSetColor(powerButton);
    ofRect(ofGetWidth()-ofGetWidth()/4-4, 7, 55, 6);
    ofSetColor(255);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
            
            // Restart the game:
        case 'r':
        case 'R':
            // Clear out the vector:
            for (int i=0; i<myDistractions.size(); i++) myDistractions.erase(myDistractions.begin(), myDistractions.end());
            setup();
            break;
            
            // Debug - make a distraction:
        case 'm':
            if (powerOn) {
                distraction distraction;
                distraction.setup(ofGetWidth()/2, ofGetHeight()/2, 5);
                myDistractions.push_back(distraction);
            }
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    if (gameState == 0) {
        
        //ofRect(ofGetWidth()/2-12, ofGetHeight()/2+142, 50, 35);
        if (mouseX >= ofGetWidth()/2-12-(50/2) && mouseX <= ofGetWidth()/2-12+(50/2) && mouseY >= ofGetHeight()/2+42-(35/2) && mouseY <= ofGetHeight()/2+42+(35/2)) gameState++;
        
    }
    
    if (gameState == 1) {
        
        // Destroy a distraction by clicking on it:
        if (powerOn) {
            
            for (int i=0; i<myDistractions.size(); i++) {
                if (ofDist(mouseX, mouseY, myDistractions[i].xPos, myDistractions[i].yPos) < myDistractions[i].wide/2) {
                    myDistractions[i].destroyMe = true;
                    if (!chaos) chaos = true;
                }
            }
            
        } // End if (powerOn).
        
        // Use the power button:
        if (mouseX >= ofGetWidth()-ofGetWidth()/4-4-(55/2) && mouseX <= ofGetWidth()-ofGetWidth()/4-4+(55/2) && mouseY >= 7-(6/2) && mouseY <= 7+(6/2)) {
            powerOn = !powerOn;
            powerButton.a = 0;
            aVel = 1;
        }
        
    } // End gameState = 1.
    
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