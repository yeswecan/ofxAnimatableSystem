
#ifndef AnimatableColor_h
#define AnimatableColor_h

#include "AnimatableObject.h"
#include "ofMain.h"

// Animatable object
class AnimatableColor: public Animatable, public ofColor {
public:
    AnimatableColor() {
        index = registerAnimatable(this_);
    }
    
    ~AnimatableColor() {
        unregisterAnimatable(this_, index);
    }

    AnimatableColor(const AnimatableColor & other): AnimatableColor() {
        ofColor::operator=(other);
        target = other.target;
        start = other.start;
    }

    ofColor operator= (ofColor righthand) {
        ofColor::operator= (righthand);
        return *this;
    }
    
    // Animatable's virtual function implementation
    
    void prepareToAnimateDifference() {
        backupValue = (*this);
    };
    
    void animateDifference() {
        if (backupValue != (*this)) {
            start = backupValue;
            target = (*this);
            (*this) = backupValue;
            if (!isAnimating()) {
                startTime = queryStartTime;
                targetTime = queryTargetTime;
                AnimatableSystem::startAnimating(this_);
            } else {
                startTime = queryStartTime;
                targetTime = queryTargetTime;
            }
        }
    };
    
    virtual void update() {
        float phase = easingFunc((timestamp - startTime) / targetTime);
        float r = (target.r - start.r) * phase + start.r;
        float g = (target.g - start.g) * phase + start.g;
        float b = (target.b - start.b) * phase + start.b;
        ofColor::operator= (ofColor(r, g, b));
    };
    
private:
    ofColor target, start, backupValue;
};

#endif 
