#include "../Include/Application.hpp"
#include "../Include/Menu.hpp"
#include "../Include/Game.hpp"

const sf::Time Application::secondsFramesRatio = sf::seconds(1.f/60.f);

Application::Application() : window(sf::VideoMode(800,576), "NukeOut!"), menuState(window), gameState(window) {
	currentState = &menuState;
}

void Application::run() {
	sf::Clock clock;
	sf::Time lastUpdate = sf::Time::Zero;
	while (window.isOpen()) {
		lastUpdate += clock.restart();
		while (lastUpdate > secondsFramesRatio) {
			lastUpdate -= secondsFramesRatio;
			
			processInput();
			update(secondsFramesRatio);
		}
		render();
	}
}

void Application::processInput() {
	sf::Event event;
		while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Q) {
				window.close();
			} else {
				if (!currentState->processInput(event)) {
					if (currentState == &menuState) {
						currentState = &gameState;
					} else if (currentState == &gameState) {
						currentState = &menuState;
					}
				}
			}
		}
	}
}

void Application::update(sf::Time delta) {
	currentState->update(delta);
}

void Application::render() {
	currentState->render();
}