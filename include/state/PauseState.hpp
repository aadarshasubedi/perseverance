#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include <SFML/Graphics/Text.hpp>
#include "state/State.hpp"

class PauseState : public State {

public:
    PauseState(StateStack& stack, Context context);

public:
    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event& event) override;

private:
    sf::Text pauseText;
    sf::Text instructionText;
};

#endif //PAUSESTATE_HPP