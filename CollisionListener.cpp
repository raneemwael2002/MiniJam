#include "CollisionListener.h"
#include<iostream>

CollisionListener::CollisionListener(Player& player,Taxi& taxi,Projectile& projectile)
    : player(player), taxi(taxi), projectile(projectile) {}

void CollisionListener::BeginContact(b2Contact* contact) {

    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    Player* playerPtr = nullptr;
    Taxi* taxiPtr = nullptr;
    Projectile* projectilePtr = nullptr;



    // Check if the first body is a player


    if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&player)) {
        playerPtr = &player;
        taxiPtr = reinterpret_cast<Taxi*>(bodyB->GetUserData().pointer);
    }
    // Check if the second body is a player
    else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&player)) {
        playerPtr = &player;
        projectilePtr = reinterpret_cast<Projectile*>(bodyB->GetUserData().pointer);
    }

    //Check if the first body is a taxi
    if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&taxi)) {
        taxiPtr = &taxi;
        playerPtr = reinterpret_cast<Player*>(bodyB->GetUserData().pointer);
    }
    else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&taxi)) {
        taxiPtr = &taxi;
        playerPtr = reinterpret_cast<Player*>(bodyA->GetUserData().pointer);
    }
    // Check if the second body is a taxi
    if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&taxi)) {
        taxiPtr = &taxi;
        projectilePtr = reinterpret_cast<Projectile*>(bodyB->GetUserData().pointer);
    }
    if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&taxi)) {
        taxiPtr = &taxi;
        projectilePtr = reinterpret_cast<Projectile*>(bodyA->GetUserData().pointer);
    }

    // Check if the first body is a projectile
    if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&projectile)) {
        projectilePtr = &projectile;
        playerPtr = reinterpret_cast<Player*>(bodyB->GetUserData().pointer);
    }
    // Check if the second body is a projectile
    else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&projectile)) {
        projectilePtr = &projectile;

    }

    // If a player collided with a taxi
    if (playerPtr && taxiPtr) {
        std::cout << "Player collided with Taxi!" << std::endl;
        // Handle player-taxi collision (e.g., take damage, bounce back, etc.)
    }

    // If a player collided with a projectile
    if (playerPtr && projectilePtr) {
        std::cout << "Player collided with Projectile!" << std::endl;
        // Handle player-projectile collision (e.g., take damage, destroy projectile, etc.)
    }

    // If a taxi collided with a projectile
    if (taxiPtr && projectilePtr) {
        std::cout << "Taxi collided with Projectile!" << std::endl;
        // Handle taxi-projectile collision (e.g., destroy taxi, destroy projectile, etc.)
    }



}







//void CollisionListener::BeginContact(b2Contact* contact)
//{
//    b2Body* bodyA = contact->GetFixtureA()->GetBody();
//    b2Body* bodyB = contact->GetFixtureB()->GetBody();
//
//    Player* playerPtr = nullptr;
//    Taxi* taxiPtr = nullptr;
//    Projectile* projectilePtr = nullptr;
//
//    if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&player)) {
//        playerPtr = &player;
//    }
//    else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&player)) {
//        playerPtr = &player;
//    }
//
//    if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&taxi)) {
//        taxiPtr = &taxi;
//    }
//    else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&taxi)) {
//        taxiPtr = &taxi;
//    }
//
//    if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&projectile)) {
//        projectilePtr = &projectile;
//    }
//    else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&projectile)) {
//        projectilePtr = &projectile;
//    }
//
//    // Handle collision events
//    if (playerPtr && taxiPtr) {
//        std::cout << "Player collided with Taxi!" << std::endl;
//        // Handle logic for collision between Player and Taxi
//    }
//
//    if (taxiPtr && projectilePtr) {
//        std::cout << "Taxi collided with Projectile!" << std::endl;
//        // Handle logic for collision between Taxi and Projectile
//    }
//}



//void CollisionListener::BeginContact(b2Contact* contact)
//{
//    b2Body* bodyA = contact->GetFixtureA()->GetBody();
//    b2Body* bodyB = contact->GetFixtureB()->GetBody();
//
//    Player* playerPtr = nullptr;
//    Taxi* taxiPtr = nullptr;
//    Projectile* projectilePtr = nullptr;
//
//    // Loop through all taxis and check for collision with bodyA and bodyB
//    for (Taxi& taxi : taxis) {
//        if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&taxi)) {
//            taxiPtr = &taxi;
//
//            if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&playerPtr)) {
//                playerPtr = reinterpret_cast<Player*>(bodyB->GetUserData().pointer);
//                std::cout << "Taxi collided with Player! (PlayerPtr: " << playerPtr << ")" << std::endl;
//            }
//            else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&projectilePtr)) {
//                projectilePtr = reinterpret_cast<Projectile*>(bodyB->GetUserData().pointer);
//                std::cout << "Taxi collided with Projectile! (ProjectilePtr: " << projectilePtr << ")" << std::endl;
//            }
//        }
//        else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&taxi)) {
//            taxiPtr = &taxi;
//
//            if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&playerPtr)) {
//                playerPtr = reinterpret_cast<Player*>(bodyA->GetUserData().pointer);
//                std::cout << "Taxi collided with Player! (PlayerPtr: " << playerPtr << ")" << std::endl;
//            }
//            else if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&projectilePtr)) {
//                projectilePtr = reinterpret_cast<Projectile*>(bodyA->GetUserData().pointer);
//                std::cout << "Taxi collided with Projectile! (ProjectilePtr: " << projectilePtr << ")" << std::endl;
//            }
//        }
//    }
//
//    // Loop through all projectiles and check for collision with bodyA and bodyB
//    for (Projectile& projectile : projectiles) {
//        if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&projectile)) {
//            projectilePtr = &projectile;
//
//            if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&playerPtr)) {
//                playerPtr = reinterpret_cast<Player*>(bodyB->GetUserData().pointer);
//                std::cout << "Projectile collided with Player! (PlayerPtr: " << playerPtr << ")" << std::endl;
//            }
//            else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&taxiPtr)) {
//                taxiPtr = reinterpret_cast<Taxi*>(bodyB->GetUserData().pointer);
//                std::cout << "Projectile collided with Taxi! (TaxiPtr: " << taxiPtr << ")" << std::endl;
//            }
//        }
//        else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&projectile)) {
//            projectilePtr = &projectile;
//
//            if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&playerPtr)) {
//                playerPtr = reinterpret_cast<Player*>(bodyA->GetUserData().pointer);
//                std::cout << "Projectile collided with Player! (PlayerPtr: " << playerPtr << ")" << std::endl;
//            }
//            else if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&taxiPtr)) {
//                taxiPtr = reinterpret_cast<Taxi*>(bodyA->GetUserData().pointer);
//                std::cout << "Projectile collided with Taxi! (TaxiPtr: " << taxiPtr << ")" << std::endl;
//            }
//        }
//    }
//}




    

