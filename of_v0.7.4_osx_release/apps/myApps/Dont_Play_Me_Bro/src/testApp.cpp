#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    grunt.setup();
    player.setup();
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (moveL) xPos--;
    if (moveR) xPos++;
    
    grunt.update();
    player.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    ofPushMatrix();
    ofTranslate(xPos, yPos);
    ofLine(0, ofGetHeight()/2+50, ofGetWidth(), ofGetHeight()/2+50);
    grunt.draw();
    ofPopMatrix();
    
    player.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    // Enable movement on keyPress:
    /*switch (key) {
        case 'w':
        case 'W':
        case OF_KEY_UP:
            player.moveUP = true;
            break;
            
        case 'a':
        case 'A':
        case OF_KEY_LEFT:
            player.moveLEFT = true;
            break;
            
        case 's':
        case 'S':
        case OF_KEY_DOWN:
            player.moveDOWN = true;
            break;
            
        case 'd':
        case 'D':
        case OF_KEY_RIGHT:
            player.moveRIGHT = true;
            break;
            
            // Restart the game:
        case 'r':
            setup();
            break;
            
            // Debug. Comment this out later.
        case 'g':
        case 'G':
            player.ghost = true;
            break;
    }*/
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    // Disable movement on keyRelease:
    /*switch (key) {
        case 'w':
        case 'W':
        case OF_KEY_UP:
            player.moveUP = false;
            break;
            
        case 'a':
        case 'A':
        case OF_KEY_LEFT:
            player.moveLEFT = false;
            break;
            
        case 's':
        case 'S':
        case OF_KEY_DOWN:
            player.moveDOWN = false;
            break;
            
        case 'd':
        case 'D':
        case OF_KEY_RIGHT:
            player.moveRIGHT = false;
            break;
            
        case 'g':
        case 'G':
            player.ghost = false;
            break;
    }*/
    
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