#pragma once

#include "ofMain.h"
//#include "UIAnimation.h"

#include "ofxAnimatableSystem.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    struct P {
        AnimatableObject<ofPoint> p;
        AnimatableColor color;
        AnimatableValue<float> size;
    };
    
    void randomizeValues() {
        for (auto i = 0; i < points.size(); i++) {
            ofPoint randomPoint = ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
            float hue = ((randomPoint.x + ofRandom(100)) / ofGetWidth()) * 125 + ((randomPoint.y + ofRandom(100)) / ofGetHeight()) * 125;
            
            points[i].p = randomPoint;
            points[i].color = ofColor::fromHsb(hue, 200, 200);
            points[i].size = ofRandom(25);
        }
    }
    
    vector<P> points;
    
    AnimatableObject<ofPoint> testP;
    
    ofxAnimatableSystem animatableSystem;
    
};
