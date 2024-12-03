#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
class Chicken {
public:
    Chicken(float x, float y, float radius) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
    }

    void update() {
        // Make the chicken move vertically downward (simple AI behavior)
        shape.move(0, 1);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::CircleShape shape;
};

class Ship {
public:
    Ship(float x, float y, float radius) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
    }

    void move(float dx, float dy) {
        shape.move(dx, dy);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::CircleShape shape;
};

class Projectile {
public:
    Projectile(float x, float y, float radius) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
        speed = 5.0f;
    }

    void update() {
        shape.move(0, -speed);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::CircleShape shape;
    float speed;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Invader-like Game");

    Chicken chicken(400, 0, 20); // Chicken at the top-center
    Ship ship(400, 500, 20);     // Ship at the bottom-center

    std::vector<Projectile> projectiles;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Move the ship with arrow keys
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            ship.move(-5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            ship.move(5, 0);
        }

        // Shoot projectiles when space is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            projectiles.push_back(Projectile(ship.shape.getPosition().x, ship.shape.getPosition().y - 20, 5));
        }

        // Update projectiles
        for (auto& projectile : projectiles) {
            projectile.update();
        }

        // Update chicken
        chicken.update();

        // Check for collision between projectiles and chicken
        for (auto& projectile : projectiles) {
            if (projectile.shape.getGlobalBounds().intersects(chicken.shape.getGlobalBounds())) {
                std::cout << "Chicken hit!" << std::endl;
                // Chicken is destroyed by projectile, reset position
                chicken.shape.setPosition(400, 0);  // Reset chicken to top-center
                break;  // Exit loop after collision
            }
        }

        // Clear the screen
        window.clear();

        // Draw everything
        chicken.draw(window);
        ship.draw(window);
        for (auto& projectile : projectiles) {
            projectile.draw(window);
        }

        // Display the content
        window.display();
    }

    return 0;
}
