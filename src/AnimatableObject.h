
#ifndef AnimatableObject_h
#define AnimatableObject_h

#include "AnimatableSystem.h"

// Animatable object.
// To make an arbitrary class animatable with this template, you have to
// make it able to be multiplied by a float value and be subctracted from another object
// of its class.

template <typename T>
class AnimatableObject: public Animatable, public T {
public:
    AnimatableObject() {
        index = registerAnimatable(this_);
    }

    ~AnimatableObject() {
        unregisterAnimatable(this_, index);
    }
    
    AnimatableObject(const AnimatableObject & other): AnimatableObject() {
        T::operator=(other);
        target = other.target;
        start = other.start;
    }

    T operator= (T righthand) {
        T::operator= (righthand);
        
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
    
    //
    
    void animateTo(T target, float duration /*,  TODO: easing func, start time */) {
        start = (*this);
        this->target = target;
        startTime = timestamp;
        targetTime = duration;
        AnimatableSystem::startAnimating(this_);
    }
    
    //

    virtual void update() {
        float phase = easingFunc((timestamp - startTime) / targetTime);
        T::operator= ((target - start) * phase + start);
    };
    
private:
    T target, start;
    
    T backupValue;
};


#endif 
