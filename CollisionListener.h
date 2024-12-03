#pragma once
#include<box2d/box2d.h>
#include "Player.h"
#include"Taxi.h"
#include"Projectile.h"
class CollisionListener : public b2ContactListener {
private:
    Player& player;
    Taxi& taxi;
    Projectile& projectile;

public:
    CollisionListener(Player& player, Taxi& taxi, Projectile& projectile);


    void BeginContact(b2Contact* contact) override;
};