#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Housekeeping:
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetCircleResolution(60);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    
    originX = originY = 0;
    groundY = ofGetHeight()-100;
    moveSpeed = 7;
    grunt.setup(ofGetWidth()/2-100, groundY);
    //grunt2.setup(ofGetWidth()+100, groundY);
    //enemies.push_back(enemeyTest);
    //enemies.push_back(enemyTest2);
    //cout<<enemies.size()<<endl;
    player.setup(ofGetWidth()/2, groundY);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (moveL) originX += moveSpeed; // Translate to the right on LEFT.
    if (moveR) originX -= moveSpeed; // Translate to the left on RIGHT.
    
    //grunt.update();
    //grunt2.update();
    for (int i = 0; i<enemies.size(); i++) enemies[i].update();
    
    player.update();
    
    for (int i=0; i<enemies.size(); i++) {
        if (ofDist(player.xPos, player.yPos, enemies[i].xPos+originX, enemies[i].yPos) < player.wide/2+enemies[i].rad) collision[i] = true;
        
    //dist = ofDist(player.xPos, player.yPos, grunt.xPos+originX, grunt.yPos);
    //if (dist < ) {player.tall = 25;}
        else collision[i] = false;
        if (collision[i]) player.tall = 25;
        else player.tall = 50;
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    ofLine(0, groundY, ofGetWidth(), groundY); // The ground.
    // The player stays in one place and the environment translates as the player moves:
    ofPushMatrix();
    ofTranslate(originX, originY);
    //grunt.draw();
    //grunt2.draw();
    for (int i=0; i<enemies.size(); i++) enemies[i].draw();
    ofPopMatrix();
    
    for (int i=0; i<enemies.size(); i++) ofLine(player.xPos, player.yPos, enemies[i].xPos+originX, enemies[i].yPos);
    player.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    // Enable movement on keyPress:
    switch (key) {
            /*case 'w':
             case 'W':
             case OF_KEY_UP:
             player.moveUP = true;
             break;*/
            
        case 'a':
        case 'A':
        case OF_KEY_LEFT:
            moveL = true;
            break;
            
            /*case 's':
             case 'S':
             case OF_KEY_DOWN:
             player.moveDOWN = true;
             break;*/
            
        case 'd':
        case 'D':
        case OF_KEY_RIGHT:
            moveR = true;
            break;
            
            // Restart the game:
        case 'r':
            setup();
            break;
            
            case 'm':
            enemy_grunt enemy;
            enemy.setup(ofGetWidth()/2+300*enemies.size(), groundY);
            enemies.push_back(enemy);
            bool collided = false;
            collision.push_back(collided);
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    // Disable movement on keyRelease:
    switch (key) {
            /*case 'w':
             case 'W':
             case OF_KEY_UP:
             player.moveUP = false;
             break;*/
            
        case 'a':
        case 'A':
        case OF_KEY_LEFT:
            moveL = false;
            break;
            
            /*case 's':
             case 'S':
             case OF_KEY_DOWN:
             player.moveDOWN = false;
             break;*/
            
        case 'd':
        case 'D':
        case OF_KEY_RIGHT:
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