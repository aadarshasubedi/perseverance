#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#include "state/State.hpp"

class TitleState : public State {

public:
    TitleState(StateStack& stack, Context context);

public:
    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event& event) override;

private:
    sf::Sprite background;
};

#endif //TITLESTATE_HPP