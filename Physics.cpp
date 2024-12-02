//#include "Physics.h"
//
//b2Vec2 Physics::calculateGravity(const b2Vec2& planetPosition, const b2Vec2& starPosition, float gravityStrength) {
//    b2Vec2 direction = starPosition - planetPosition;
//    float distance = direction.Length();
//
//    // Avoid division by zero
//    if (distance < 1.0f) distance = 1.0f;
//
//    float forceMagnitude = gravityStrength / (distance * distance);
//    direction.Normalize();
//    return forceMagnitude * direction;
//}
