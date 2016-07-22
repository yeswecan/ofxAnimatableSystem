#ifndef AnimatableSystem_h
#define AnimatableSystem_h

#include "Animatable.h"

// The class that holds it all together
class AnimatableSystem {
public:
    AnimatableSystem() {
        initialize();
    }
    
    //
    
    static float getTimestamp() {
        return Animatable::getTimestamp();
    }
    
    // User call this when he or she wants to perform animations in a given closure
    // in a given duration.

    static void animateWithDuration(float duration, std::function<void()> animations) {
        Animatable::startAssigningToTarget(duration);
        animations();
        Animatable::stopAssigningToTarget();
    }
    
    // Animatables call this when they start animating.
    
    static void startAnimating(shared_ptr<Animatable> entity) {
        animatedEntities.push_back(entity);
    }
    
    
private:
    static vector<weak_ptr<Animatable>> animatedEntities;
    
    void initialize() {
        ofAddListener(ofEvents().update, this, &AnimatableSystem::update);
    }
    
    void update(ofEventArgs & args) {
        
        Animatable::updateTimestamp();
        
        int i = 0;
        while (i < animatedEntities.size()) {
            if (auto j = animatedEntities[i].lock()) {
                j->update();
                if (!j->isAnimating()) animatedEntities.erase(animatedEntities.begin() + i);
            }
            i++;
        }
        
    }
    
};

#endif /* ofxAnimatableSystem_h */
