#include "Player.hpp"
#include "scene/Creature.hpp"

#include <scene/CommandQueue.hpp>

struct PlayerMover {
    PlayerMover(float velocityX, float velocityY, Heading heading)
            : velocity(velocityX, velocityY),
              heading(heading) {
    }

    void operator()(Creature& creature, sf::Time deltaTime) const {
        creature.accelerate(velocity * creature.getSpeed());
        creature.setHeading(heading);
    }

    sf::Vector2f velocity;
    Heading heading;
};

Player::Player() {
    keyBinding[sf::Keyboard::Key::W] = Action::MoveNorth;
    keyBinding[sf::Keyboard::Key::A] = Action::MoveWest;
    keyBinding[sf::Keyboard::Key::S] = Action::MoveSouth;
    keyBinding[sf::Keyboard::Key::D] = Action::MoveEast;

    initializePlayerActions();

    for (auto &pair : actionBinding) {
        pair.second.categoryFilter = Category::Hero;
    }
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands) {
    if (sf::Event::KeyPressed == event.type) {
        auto searchKeyBinding = keyBinding.find(event.key.code);
        if (keyBinding.end() != searchKeyBinding && !isRealTimeAction(searchKeyBinding->second)) {
            commands.push(actionBinding[searchKeyBinding->second]);
        }
    }
}

void Player::handleRealtimeInput(CommandQueue &commands) {
    for (auto pair : keyBinding) {
        if (sf::Keyboard::isKeyPressed(pair.first)
                && isRealTimeAction(pair.second)) {
            Command &command = actionBinding[pair.second];
            commands.push(command);
        }
    }
}

void Player::initializePlayerActions() {
    actionBinding[Action::MoveNorth].action = sceneNodeAction<Creature>(PlayerMover(0.f, -1.f, Heading::North));
    actionBinding[Action::MoveWest].action = sceneNodeAction<Creature>(PlayerMover(-1.f, 0.f, Heading::West));
    actionBinding[Action::MoveSouth].action = sceneNodeAction<Creature>(PlayerMover(0.f, 1.f, Heading::South));
    actionBinding[Action::MoveEast].action = sceneNodeAction<Creature>(PlayerMover(1.f, 0.f, Heading::East));
}

void Player::assignKey(sf::Keyboard::Key key, Action action) {
    for (auto itr = keyBinding.begin(); itr != keyBinding.end();) {
        if (action == itr->second) {
            keyBinding.erase(itr++);
        } else {
            itr++;
        }
    }

    keyBinding[key] = action;
}

sf::Keyboard::Key Player::getKeyForAction(Action action) const {
    sf::Keyboard::Key key = sf::Keyboard::Unknown;

    for (auto pair : keyBinding) {
        if (action == pair.second) {
            key = pair.first;
            break;
        }
    }

    return key;
}

bool Player::isRealTimeAction(Action action) {
    bool result = false;

    switch (action) {
        case Action::MoveNorth :
        case Action::MoveWest :
        case Action::MoveSouth :
        case Action::MoveEast :
            result = true;
    }

    return result;
}