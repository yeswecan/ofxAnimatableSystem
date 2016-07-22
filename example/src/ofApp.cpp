#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    while (points.size() < 3000) {
        P addition;
        addition.p = ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        addition.color = ofColor::fromHsb(ofRandom(255), 200, 200);
        addition.size = ofRandom(25);
        points.push_back(addition);
    }
    
    
    std::unordered_map<long, AnimatableObject<ofPoint>*> map;
    map[123] = new AnimatableObject<ofPoint>(); *map[123] = ofPoint(1);
    map[213] = new AnimatableObject<ofPoint>(); *map[213] = ofPoint(2);
    map[5000] = new AnimatableObject<ofPoint>(); *map[5000] = ofPoint(3);
    map[5001] = new AnimatableObject<ofPoint>(); *map[5001] = ofPoint(4);
    for (auto i: map) {
        ofLog() << i.first << " : " << *i.second;
    }
    
    testP = ofPoint(300, 300);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (auto i = 0; i < points.size(); i++) {
        ofSetColor(points[i].color);
        ofPoint movement = ofPoint(sin(Animatable::getTimestamp() * sin(i / 2) + i) * 20 * sin(i / 2),
                                   cos(Animatable::getTimestamp() * cos(i / 2) + i) * 20 * cos(i / 2));
        ofCircle(points[i].p + movement, points[i].size + 2 * sin(ofGetElapsedTimef() + i));
    }
    
    ofSetColor(255);
    ofDrawBitmapStringHighlight("Objects on screen :" + ofToString(Animatable::getPointerCount()), 50, 50);
    ofDrawBitmapStringHighlight("Press space to animate them all to different points.", 50, 70);
    ofDrawBitmapStringHighlight("Press `z` to set them all to different points.", 50, 90);
    ofDrawBitmapStringHighlight("Click anywhere on screen to animate that blinking circle there.", 50, 90);
    
    
    ofSetColor(ofRandom(255));
    ofCircle(testP, 50);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 32) {
        
        // Syntax:
        // ofxAnimatableSystem::animateWithDuration(float animationDuration, [&]() { /* end result of animation */ })
        
        ofxAnimatableSystem::animateWithDuration(3, [&]() {
            
            // Inside these brackets you assign to all the AnimatableObjects, AnimatableColors and AnimatableValues
            // the values you want them to become as the end result of animation. This particular animation
            // will last 3 seconds, as it's stated in animateWithDuration() function call above this lambda function.
            
            randomizeValues();
        });
    }
    
    // TODO: when you press 'z' in the middle of animation, animation doesn't stop as expected.
    if (key == 'z') {
        randomizeValues();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    testP.animateTo(ofPoint(x, y), 2);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
