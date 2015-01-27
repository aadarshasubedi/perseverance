#include "Player.hpp"
#include "Hero.hpp"

#include <util/CommandQueue.hpp>
#include <util/Command.hpp>

struct HeroMover {
    HeroMover(float velocityX, float velocityY, Hero::Heading heading)
            : velocity(velocityX, velocityY),
              heading(heading) {
    }

    void operator()(Hero &hero, sf::Time deltaTime) const {
        hero.setVelocity(velocity);
        hero.setHeading(heading);
    }

    sf::Vector2f velocity;
    Hero::Heading heading;
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
    const static float playerSpeed = 90.f;

    actionBinding[Action::MoveNorth].action = sceneNodeAction<Hero>(HeroMover(0.f, -playerSpeed, Hero::Heading::North));
    actionBinding[Action::MoveWest].action = sceneNodeAction<Hero>(HeroMover(-playerSpeed, 0.f, Hero::Heading::West));
    actionBinding[Action::MoveSouth].action = sceneNodeAction<Hero>(HeroMover(0.f, playerSpeed, Hero::Heading::South));
    actionBinding[Action::MoveEast].action = sceneNodeAction<Hero>(HeroMover(playerSpeed, 0.f, Hero::Heading::East));
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