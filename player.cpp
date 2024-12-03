//#include "player.h"
//
//Player::Player(b2World& world, float x, float y, float r, float scaleFactor)
//    : radius(r), scale(scaleFactor) {
//    // Box2D body setup
//    b2BodyDef bodyDef;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.position.Set(x / scale, y / scale);
//    body = world.CreateBody(&bodyDef);
//
//    b2CircleShape circleShape;
//    circleShape.m_radius = radius / scale;
//
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &circleShape;
//    fixtureDef.density = 0.01f;
//    body->CreateFixture(&fixtureDef);
//    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
//    // SFML shape setup
//    shape.setRadius(radius);
//    shape.setFillColor(sf::Color::Red);
//    shape.setOrigin(radius, radius);
//    shape.setPosition(x, y);
//}
//
//Player::~Player() {
//    if (body && body->GetWorld()) {
//        body->GetWorld()->DestroyBody(body);
//    }
//}
//
//void Player::draw(sf::RenderWindow& window) {
//    window.draw(shape);
//    for (auto& projectile : projectiles) {
//        projectile.draw(window);
//    }
//}
//
//void Player::update() {
//
//
//    shape.setPosition(body->GetPosition().x * scale, body->GetPosition().y * scale);
//
//    for (auto it = projectiles.begin(); it != projectiles.end();) {
//        it->update();
//        if (it->getPosition().y < 0) { // Off-screen condition (e.g., above the screen)
//            it = projectiles.erase(it); // Remove from vector
//        }
//        else {
//            ++it;
//        }
//    }
//}
//
//void Player::handleInput(b2World& world) {
//    b2Vec2 velocity(0.0f, 0.0f);
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//        if (body->GetPosition().x < 350 / scale)
//        {
//            velocity.x += moveSpeed;
//        }
//        else
//            velocity.x -= moveSpeed;
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//        if (body->GetPosition().x > 870 / scale)
//        {
//            velocity.x -= moveSpeed;
//        }
//        else
//            velocity.x += moveSpeed;
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//        velocity.y -= moveSpeed;
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//        velocity.y += moveSpeed;
//    }
//
//    if (velocity.Length() > 0.0f) {
//        velocity.Normalize();
//        velocity *= moveSpeed;
//    }
//
//    body->SetLinearVelocity(velocity);
//
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//        float cooldownTime = 0.3f;
//        if (shootClock.getElapsedTime().asSeconds() > cooldownTime) {
//            float speed = 400.0f;
//            float angle = -90.0f * (3.14f / 180.0f);
//            projectiles.emplace_back(world, shape.getPosition().x, shape.getPosition().y, speed, angle, 5.0f, scale);
//            shootClock.restart();
//        }
//    }
//
//
//}
//
//const std::vector<Projectile>& Player::getProjectiles() const {
//    return projectiles;
//}
//
//void Player::clearProjectiles() {
//    projectiles.clear();
//}
//
//b2Vec2 Player::getPosition() const {
//    return body->GetPosition();
//}
//
