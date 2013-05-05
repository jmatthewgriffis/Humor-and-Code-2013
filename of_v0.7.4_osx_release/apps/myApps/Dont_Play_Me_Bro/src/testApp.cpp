#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofNoFill();
    xPos = 0;
    yPos = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (moveL) xPos--;
    if (moveR) xPos++;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    ofPushMatrix();
    ofTranslate(xPos, yPos);
    ofLine(0, ofGetHeight()/2+50, ofGetWidth(), ofGetHeight()/2+50);
    ofCircle(ofGetWidth()/2-100, ofGetHeight()/2+25, 25);
    ofPopMatrix();
    ofRect(ofGetWidth()/2, ofGetHeight()/2, 50, 50);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch(key) {
        case 'a':
            moveL = true;
            break;
            
        case 'd':
            moveR = true;
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    switch(key) {
        case 'a':
            moveL = false;
            break;
            
        case 'd':
            moveR = false;
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