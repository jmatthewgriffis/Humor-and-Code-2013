#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(24);
    ofSetWindowShape(1024, 768);
    
    cam.initGrabber(320, 240);
    colorImage.allocate(320, 240);
    grayImage.allocate(320, 240);
    bgImage.allocate(320, 240);
    absDiffImage.allocate(320, 240);
    
    threshold = 55;
    
}

//--------------------------------------------------------------
void testApp::update(){
    cam.update();
    if(cam.isFrameNew()) {
        colorImage.setFromPixels( cam.getPixelsRef() );
        colorImage.mirror(false, true); // First is vertical, second is horizontal.
        grayImage = colorImage; // This is operator overload - the equal sign within the grayscaleimage class runs a function to convert the image type.
        absDiffImage.absDiff(bgImage, grayImage);
        absDiffImage.threshold( threshold );
        
        absDiffImage.erode();
        absDiffImage.erode();
        absDiffImage.dilate();
        absDiffImage.dilate();
        
        contourFinder.findContours(absDiffImage, 320*240*0.1, 320*240*0.8, 3, false);
        
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    //cam.draw(20,20);
    colorImage.draw(360, 20);
    //grayImage.draw(700, 20);
    //bgImage.draw(20, 290);
    //absDiffImage.draw(360,290);
    //contourFinder.draw(720,290);
    contourFinder.draw(360,20);
    
    ofDrawBitmapString("threshold = " + ofToString(threshold), 5, ofGetHeight()-5);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key==' ') {
        bgImage = grayImage;
    }
    
    if (key==OF_KEY_UP) {
        threshold+=5;
    }
    
    if (key==OF_KEY_DOWN) {
        threshold-=5;
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