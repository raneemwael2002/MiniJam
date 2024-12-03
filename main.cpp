#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Player.h"
#include"projectile.h"
#include<iostream>
#include<vector>
#include <string>
const float SCALE = 4.0f;
enum class GameState {
	MAIN_MENU,
	GAMEPLAY,
	EXIT
};






int main() {

	sf::RenderWindow window(sf::VideoMode(1200, 1000), "Embaba Invaders");
	GameState currentState = GameState::MAIN_MENU;
	//window.setFramerateLimit(60);
	std::vector<sf::Texture> menuBackgroundFrames;
		sf::Texture texture;
	for (int i = 0; i < 30; ++i) { // 120 frames

		std::string filename = "E:/Game dev/Mini Jam/box2d/Frames/Animated Menu_" +
			std::to_string(100000 + i).substr(1) + ".png";

		if (texture.loadFromFile(filename)) {
			
			menuBackgroundFrames.push_back(texture);
		}
		else {
			std::cerr << "Failed to load: " << filename << std::endl;
		}
	}
	if (menuBackgroundFrames.empty()) {
		std::cerr << "Failed to load menu background frames!" << std::endl;
		return -1;
	}

	sf::Sprite backgroundSprite;
	size_t frameIndex = 0;
	sf::Clock animationClock;

	// Load button image
	//sf::Texture buttonTexture;
	//if (!buttonTexture.loadFromFile("DDD.png")) {
	//	std::cerr << "Failed to load button image!" << std::endl;
	//	return -1;
	//}
	//sf::Sprite buttonSprite(buttonTexture);
	//buttonSprite.setPosition(50, 0); // Position the buttons

	sf::FloatRect playButton(424, 595, 277, 65);  
	sf::FloatRect exitButton(426, 725, 232, 56);


	sf::SoundBuffer jumpBuffer;
	if (!jumpBuffer.loadFromFile("jump.wav")) {
		std::cerr << "Error loading jump.wav" << std::endl;

	}
	sf::Sound jumpSound;
	jumpSound.setBuffer(jumpBuffer);






	sf::SoundBuffer mainMenuBuffer;
	if (!mainMenuBuffer.loadFromFile("mainMenu.mp3")) {
		std::cerr << "Error loading mainnemnu.mp3" << std::endl;

	}
	sf::Sound mainMenuSound;
	mainMenuSound.setBuffer(mainMenuBuffer);

	
	sf::Cursor defaultCursor, handCursor;
	if (!defaultCursor.loadFromSystem(sf::Cursor::Arrow) ||
		!handCursor.loadFromSystem(sf::Cursor::Hand)) {
		return -1; 
	}

	window.setMouseCursor(defaultCursor);


	if (currentState == GameState::MAIN_MENU) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			if (playButton.contains(mousePos.x, mousePos.y)) {
				currentState = GameState::GAMEPLAY; 
			}
			else if (exitButton.contains(mousePos.x, mousePos.y)) {
				currentState = GameState::EXIT;
			}
		}
	}


	b2Vec2 gravity(0.f, 0.0f);
	b2World world(gravity);


	Player player(world, window.getSize().x / 2.f, 750.f, 20.f, SCALE);

	b2BodyDef groundDef;
	groundDef.type = b2_staticBody;
	groundDef.position.Set(400 / SCALE, 600 / SCALE);
	b2Body* ground = world.CreateBody(&groundDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(400 / SCALE, 10 / SCALE);
	ground->CreateFixture(&groundShape, 0.0f);


	sf::CircleShape ballShape(20.0f);
	ballShape.setFillColor(sf::Color::Red);
	ballShape.setOrigin(20.0f, 20.0f);

	float timeStep = 1.0f / 60.0f; // 60 FPS

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window.close();
			}
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			if (playButton.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))||
				exitButton.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
				window.setMouseCursor(handCursor);
			}
			else {
				window.setMouseCursor(defaultCursor);
			}
		

		}

		int32 velocityIterations = 8;
		int32 positionIterations = 3;
		world.Step(timeStep, velocityIterations, positionIterations);

		ballShape.setPosition(player.getPosition().x * SCALE, player.getPosition().y * SCALE);

		window.clear();
		

		
		switch (currentState) {

		case GameState::MAIN_MENU: {
			mainMenuSound.play();

			if (animationClock.getElapsedTime().asSeconds() > 0.1f) { // 0.1s per frame
				//backgroundSprite.setPosition(sf::Vector2f(50, 0));
				//backgroundSprite.setScale(sf::Vector2f(0.2f, 0..2f));

				frameIndex = (frameIndex + 1) % menuBackgroundFrames.size();
				backgroundSprite.setTexture(menuBackgroundFrames[frameIndex]);


				animationClock.restart();
			}

		//	window.draw(buttonSprite);     // Draw buttons
			window.draw(backgroundSprite); // Draw animated background

			// Handle button clicks
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (playButton.contains(mousePos.x, mousePos.y)) {
					currentState = GameState::GAMEPLAY; // Switch to gameplay
				}
				else if (exitButton.contains(mousePos.x, mousePos.y)) {
					currentState = GameState::EXIT; // Exit the game
				}
			}
			break;
		}

		case GameState::GAMEPLAY: {
			// Gameplay logic
			int32 velocityIterations = 8;
			int32 positionIterations = 3;
			world.Step(timeStep, velocityIterations, positionIterations);

			ballShape.setPosition(player.getPosition().x * SCALE, player.getPosition().y * SCALE);

			player.wallCollision(&window);
			player.handleInput(jumpSound);
			player.update();
			player.draw(window);
			window.draw(ballShape);
			
			break;
		}

		case GameState::EXIT:
			window.close();
			break;
		}

		window.display();
	}

	return 0;
	
}
