#include "Animatable.h"


// Animatable

vector<weak_ptr<Animatable>> Animatable::animatables;
float Animatable::timestamp;
bool Animatable::assignToTarget;
float Animatable::queryStartTime, Animatable::queryTargetTime;