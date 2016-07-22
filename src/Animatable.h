
#ifndef Animatable_h
#define Animatable_h


#include <functional>
#include "ofMain.h"
#include "Curves.h"

// Base class for all the animatable classes
class Animatable: Curves {
    
    struct null_deleter
    {
        void operator()(void const *) const
        {
        }
    };
    
public:
    Animatable(): this_(this, null_deleter()) {
    }
    
    ~Animatable() {
        this_.reset();
    };
    
    virtual void update() {};
    
    bool isAnimating() {
        if ((targetTime + startTime) > timestamp)
            return true;
        
        return false;
    }
    
    // Update static time available from everywhere
    
    static void updateTimestamp() {
        timestamp = ofGetElapsedTimef();
    }
    
    static float getTimestamp() {
        return timestamp;
    }
    
    // Register newly created Animatable object. Called from Animatable's constructor.
    
    // TODO: rewrite this to return int identifier to caller, so it'll
    // be possible for caller to delete himself later. It'll require
    // animatables vector's refactoring to map probably
    static long registerAnimatable(shared_ptr<Animatable> newcomer) {
        weak_ptr<Animatable> p = newcomer;
        animatables.push_back(p);
        return animatables.size() - 1;
    }
    
    // Unregister animatable object as it goes out of scope.
    static void unregisterAnimatable(shared_ptr<Animatable> animatable, long index = 0) {
        eraseRedundantPointers();
    }
    
    // Check if there's pointers that got freed from some other code
    
    static void eraseRedundantPointers() {
        int i = 0;
        while (i < animatables.size()) {
            if (animatables.at(i).expired()) animatables.erase(animatables.begin() + i);
            i++;
        }
    }
    
    static int getPointerCount() {
        return animatables.size();
    }
    
    // Alert all Animatables that the next operations are supposed to change
    // their target values, not the actual ones.
    
    static void startAssigningToTarget(float targetTime, float startTime = timestamp) {
        eraseRedundantPointers();
        queryTargetTime = targetTime;
        queryStartTime = startTime;
        for (auto i: animatables) {
            if (auto p = i.lock()) {
                p->prepareToAnimateDifference();
            }
        }
        assignToTarget = true;
    }
    
    static void stopAssigningToTarget() {
        for (auto i: animatables) {
            if (auto p = i.lock()) {
                p->animateDifference();
            }
        }
        assignToTarget = false;
    }
    
protected:
    
    // Class variables
    
    static float queryTargetTime, queryStartTime;
    static bool assignToTarget; // If this flag is on,
                                // we're not setting the value, but setting the animation
                                // taget instead.
    static vector<weak_ptr<Animatable>> animatables;
    static float timestamp;
    
    // These functions are there for children to support the fancy animation syntax.
    
    virtual void prepareToAnimateDifference() = 0;
    virtual void animateDifference() = 0;
    
    
    // Single Animatable's parameters
    
    float targetTime = 0, startTime = 0;
    function<double(double)> easingFunc = easeOut;
    /*
        [&](double arg)->double { return pow(arg, 3) / (pow(arg, 3) + pow(1 - arg, 3)); }; */

    // Inner shared_ptr is required for Animatables to generate weak_ptrs for themselves
    
    shared_ptr<Animatable> this_;
    long index;
};

#endif