#include "player.h"
#include"converter.h"


Player::Player(b2World& world, float x, float y, float r, float scaleFactor)
    : radius(r), scale(scaleFactor) {

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / scale, y / scale); 
    body = world.CreateBody(&bodyDef);

    
    b2CircleShape circleShape;
    circleShape.m_radius = radius / scale; 

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f; 
    body->CreateFixture(&fixtureDef);

    
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(radius, radius); 
    shape.setPosition(x, y);
}

Player::~Player() {

    if (body && body->GetWorld()) {
        body->GetWorld()->DestroyBody(body);
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

b2Vec2 Player::getPosition() const {
    return body->GetPosition();
}

void Player::applyForce(const b2Vec2& force) {
    body->ApplyForceToCenter(force, true);
}


void Player::update() {
    b2Vec2 position = body->GetPosition();
    shape.setPosition(position.x * scale, position.y * scale); // Convert Box2D to SFML units
    shape.setRotation(body->GetAngle() * 180 / b2_pi);
}



void Player::handleInput() {
    b2Vec2 currentPosition = body->GetPosition();

    
    float moveSpeed = 0.005f;  
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        currentPosition.x -= moveSpeed; // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        currentPosition.x += moveSpeed; // Move right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        currentPosition.y -= moveSpeed; // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        currentPosition.y += moveSpeed; // Move down
    }

    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        currentPosition.y -= 0.2f;  
    }

    // Set new position to the Box2D body (apply directly)
    body->SetTransform(currentPosition, body->GetAngle());
}


//void Player::wallCollision(sf::RenderTarget* target) {
//    // Check collision for the head of the snake
//    if (!snakeBody.empty()) {
//        sf::CircleShape& head = snakeBody[0];
//        float radius = head.getRadius();
//
//        // Left wall collision (handled as per your code)
//        if (head.getPosition().x < 15.f) {
//            head.setPosition(15.f, head.getPosition().y);  // Keep it at the left border
//        }
//
//        // Right wall collision
//        if (head.getPosition().x + radius >= target->getSize().x - 35.f) {
//            head.setPosition(target->getSize().x - radius - 35.f, head.getPosition().y);  // Keep it within the right border
//        }
//
//        // Top wall collision
//        if (head.getPosition().y < 15.f) {
//            head.setPosition(head.getPosition().x, 15.f);  // Keep it at the top border
//        }
//
//        // Bottom wall collision
//        if (head.getPosition().y + radius > target->getSize().y - 35.f) {
//            head.setPosition(head.getPosition().x, target->getSize().y - radius - 35.f);  // Keep it within the bottom border
//        }
//    }
//}
//


