#include "Game.hpp"

//const unsigned int Game::FrameRate = 60;
//const sf::Time Game::TimePerFrame = sf::seconds(1.f/(Game::FrameRate * 1.f));

Game::Game(sf::Vector2i screenDimensions)
        : renderWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Perseverance"),
          world(renderWindow) {

//    renderWindow.setFramerateLimit(FrameRate);
}

//void Game::run() {
//    sf::Clock frameClock;
//    sf::Time timeSinceLastUpdate = sf::Time::Zero;
//
//    while (renderWindow.isOpen()) {
//        processEvents();
//
//        sf::Time elapsedTime = frameClock.restart();
//        timeSinceLastUpdate += elapsedTime;
//
//        while (timeSinceLastUpdate > TimePerFrame) {
//            timeSinceLastUpdate -= TimePerFrame;
//            processEvents();
//            update(TimePerFrame);
//        }
//
//        render();
//    }
//}

void Game::processEvents() {
    CommandQueue& commandQueue = world.getCommandQueue();
    sf::Event event;
    while (renderWindow.pollEvent(event)) {
        player.handleEvent(event, commandQueue);

        if (sf::Event::Closed == event.type) {
            renderWindow.close();
        } else if (sf::Event::KeyPressed == event.type
                && sf::Keyboard::Escape == event.key.code) {
            renderWindow.close();
        } else if (sf::Event::Resized == event.type) {
            world.resizeView(event.size.width, event.size.height);
        }
    }

    player.handleRealtimeInput(commandQueue);
}

void Game::update(sf::Time deltaTime) {
    world.update(deltaTime);
}

void Game::render() {
    renderWindow.clear();
    world.draw();
    renderWindow.display();
}