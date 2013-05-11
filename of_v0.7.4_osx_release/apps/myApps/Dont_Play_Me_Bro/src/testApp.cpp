#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Housekeeping:
    framerate = 0;
    framerateNormal = 60;
    frameRateSlow = framerateNormal/2;
    ofSetVerticalSync(true);
    ofSetFrameRate(framerateNormal);
    ofSetCircleResolution(60);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    
    originX = originY = 0;
    groundY = ofGetHeight()-100;
    moveSpeed = 7;
    enemyRate = 2; // This many seconds between enemy appearances.
    enemyRateCounter = 0;
    maxEnemies = 10;
    xeno = 0.1; // How quickly an attack closes the distance (bigger = faster).
    storeI = 0;
    moveL = moveR = collided = slow = vanish = false;
    moveR = true;
    
    player.setup(ofGetWidth()/2-ofGetWidth()/4, groundY);
    
}

//--------------------------------------------------------------
bool bShouldIErase(enemy_grunt & a){
    
    // Zach showed me how to use this method to remove an element from a vector. We create a boolean function, i.e. one that will return a boolean (so we don't use 'void'). We feed it a class and pass a reference label that we make up (in this case 'a') so we can refer to the applicable object. Then we check for a certain condition -- in this case whether the object has moved too far offscreen or been defeated -- and if so we return a boolean value of 'true.' Otherwise it's 'false.'
    
    if (a.stageRight || a.pwned) return true;
    else return false;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (slow) framerate = frameRateSlow;
    else framerate = framerateNormal;
    ofSetFrameRate(framerate);
    
    if (moveL) originX += moveSpeed; // Translate to the right on LEFT.
    if (moveR) originX -= moveSpeed; // Translate to the left on RIGHT.
    
    // Advance the screen automatically:
    //moveR = true;
    
    // Advance the counter once per second:
    if (enemyRateCounter < enemyRate) enemyRateCounter += 1/framerateNormal;
    
    // Generate enemies automatically at the pace we set in setup():
    if (enemyRateCounter >= enemyRate && enemies.size() < maxEnemies) {
        enemy_grunt enemy;
        // Position them just offscreen to the right, taking into account the changing position of the origin:
        enemy.setup(ofGetWidth()+fabs(originX)+100, groundY);
        enemies.push_back(enemy);
        enemyRateCounter = 0;
    }
    
    for (int i = 0; i<enemies.size(); i++) enemies[i].update(originX);
    
    player.update(framerate);
    
    // Detect a collision between the player and an enemy:
    collided = false; // Set this to false by default, overwritten by collision:
    for (int i=0; i<enemies.size(); i++) {
        
        float enemyDistance = ofDist(player.xPos, player.yPos, enemies[i].xPos+originX, enemies[i].yPos);
        
        float attackDistance = (player.wide/2+enemies[i].rad)*3;
        
        float defeatDistance = player.wide/2+enemies[i].rad;
        
        if (enemyDistance < attackDistance) {
            storeI = i;
            collided = true;
            if (enemyDistance < defeatDistance) {
                enemies[i].pwned = true; // The enemy is defeated.
                player.kickAss = false;
            }
        }
        else player.jump = false;
    }
    
    if (player.vanish) moveR = false;
    
    // Do something to the player on collision:
    if (collided) {
        slow = true;
        player.jump = true;
        player.tall = 25;
    }
    if (player.kickAss) {
        player.xPos -= xeno * ofDist(player.xPos, player.yPos, enemies[storeI].xPos+originX, player.yPos);
        player.yPos += xeno * ofDist(player.xPos, player.yPos, player.xPos, enemies[storeI].yPos);
    }
    else {
        slow = false;
        player.tall = 50;
    }
    
    cout<<storeI<<endl;
    
    // Following up the boolean function we created above, this oF function sorts the vector according to the values of the booleans and then removes any with a 'true' value:
    ofRemove(enemies,bShouldIErase);
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    
    // Draw the ground:
    ofLine(0, groundY, ofGetWidth(), groundY);
    
    // The player stays in one place and everything else translates as the player "moves":
    ofPushMatrix();
    ofTranslate(originX, originY);
    for (int i=0; i<enemies.size(); i++) enemies[i].draw();
    ofPopMatrix();
    
    // Debug - draw a line from the center of each enemy to just above the player:
    for (int i=0; i<enemies.size(); i++) {
        ofLine(player.xPos, player.yPos-200, enemies[i].xPos+originX, enemies[i].yPos);
    }
    
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
            // Clear out the vector:
            for (int i=0; i<enemies.size(); i++) enemies.erase(enemies.begin(), enemies.end());
            setup(); // Reload from the top.
            break;
            
            // Debug - generate an enemy on command:
        case 'm':
            enemy_grunt enemy;
            enemy.setup(ofGetWidth()/2+300*enemies.size(), groundY);
            enemies.push_back(enemy);
            break;
            
            // Make a jump:
            case ' ':
            player.jump = true;
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
            
            // Deny a jump:
        case ' ':
            player.jump = false;
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