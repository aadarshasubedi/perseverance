#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "scene/Command.hpp"

#include <SFML/Window/Event.hpp>
#include <map>

class CommandQueue;

class Player {
public:
    enum class Action : unsigned int {
        MoveNorth,
        MoveSouth,
        MoveWest,
        MoveEast,
        ActionCount
    };

public:
    Player();

public:
    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealtimeInput(CommandQueue& commands);

private:
    void initializePlayerActions();
    void assignKey(sf::Keyboard::Key key, Action action);
    sf::Keyboard::Key getKeyForAction(Action action) const;
    static bool isRealTimeAction(Action action);

private:
    std::map<sf::Keyboard::Key, Action> keyBinding;
    std::map<Action, Command> actionBinding;
};

#endif //PLAYER_HPP