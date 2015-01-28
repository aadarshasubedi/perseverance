#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "state/State.hpp"
#include "World.hpp"
#include "Player.hpp"

class GameState : public State {

public:
    GameState(StateStack& stack, Context context);

public:
    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event& event) override;

private:
    World world;
    Player player;
};

#endif //GAMESTATE_HPP