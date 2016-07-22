
#ifndef AnimatableValue_h
#define AnimatableValue_h

#include "AnimatableSystem.h"

// Animatable value (i.e. simple variable wrapped in an Animatable class)

template <typename T>
class AnimatableValue: public Animatable {
public:
    
    AnimatableValue() {
        index = registerAnimatable(this_);
    }
    
    ~AnimatableValue() {
        unregisterAnimatable(this_, index);
    }

    AnimatableValue(const AnimatableValue & other): AnimatableValue() {
        inner = other.inner;
        target = other.target;
        start = other.start;
    }

    operator T () {
        return inner;
    }
    
    T operator* (T righthand) {
            inner = inner * righthand;
            return inner;
    }
    
    T operator+= (T righthand) {
            inner = inner + righthand;
            return inner;
    }

    T operator-= (T righthand) {
            inner = inner - righthand;
            return inner;
    }
    
    T operator= (T righthand) {
            inner = righthand;
            return inner;
    }
    
    
    // Animatable's virtual function implementation
    
    void prepareToAnimateDifference() {
        backup = inner;
    };
    
    void animateDifference() {
        if (inner != backup) {
            startTime = queryStartTime;
            targetTime = queryTargetTime;
            target = inner;
            start = backup;
            inner = start;
            if (!isAnimating()) AnimatableSystem::startAnimating(this_);
        }
    };
    
    void update() {
        float phase = easingFunc((timestamp - startTime) / targetTime);
        inner = (target - start) * phase + start;
    };
    
    
private:
    T inner, target, start, backup;
};

#endif
