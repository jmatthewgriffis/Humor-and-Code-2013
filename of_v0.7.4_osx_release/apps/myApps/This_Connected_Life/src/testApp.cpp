#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Housekeeping:
    ofSetVerticalSync(true);
    ofSetCircleResolution(60);
    ofSetFrameRate(60);
    ofSetRectMode(OF_RECTMODE_CENTER);
    verticalRez = 768;
    
    iPhone.loadImage("iphone.jpg");

}

//--------------------------------------------------------------
void testApp::update(){
    
    for (int i=0; i<myDistractions.size(); i++) myDistractions[i].update();

}

//--------------------------------------------------------------
void testApp::draw(){
    
    // Draw the image proportionately based on varying the height:
    iPhone.draw(ofGetWidth()/2, ofGetHeight()/2, iPhone.getWidth()*(verticalRez/iPhone.getHeight()), verticalRez);
    
    // Draw a rect to cover the contents of the phone's screen:
    ofRect(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()-65, ofGetHeight()-210);
    
    for (int i=0; i<myDistractions.size(); i++) myDistractions[i].draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
            
            // Debug - make a distraction:
            case 'm':
            distraction distraction;
            distraction.setup(ofGetWidth()/2, ofGetHeight()/2);
            myDistractions.push_back(distraction);
            break;
            
            // Restart the game:
            case 'r':
            case 'R':
            // Clear out the vector:
            for (int i=0; i<myDistractions.size(); i++) myDistractions.erase(myDistractions.begin(), myDistractions.end());
            setup();
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