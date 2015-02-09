#include "state/GameState.hpp"

#include <SFML/Graphics.hpp>

GameState::GameState(StateStack &stack, Context context)
        : State(stack, context),
          world(*(context.window)) {
}

bool GameState::handleEvent(const sf::Event &event) {
    CommandQueue& commandQueue = world.getCommandQueue();
    player.handleEvent(event, commandQueue);

    if (sf::Event::Resized == event.type) {
        world.resizeView(event.size.width, event.size.height);
    } else if (sf::Event::KeyPressed == event.type
            && sf::Keyboard::Escape == event.key.code) {
        requestStackPush(StateId::Pause);
    }

    return true;
}

bool GameState::update(sf::Time deltaTime) {
    world.update(deltaTime);

    CommandQueue& commandQueue = world.getCommandQueue();
    player.handleRealtimeInput(commandQueue);
}

void GameState::draw() {
    world.draw();
}