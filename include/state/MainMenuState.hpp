#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "state/State.hpp"

class MainMenuState : public State {

public:
    MainMenuState(StateStack& stack, Context context);

public:
    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event& event) override;

private:
    enum Options {
        Play,
        Exit
    };

private:
    void updateTextColor();

private:
    std::vector<sf::Text> options;
    sf::Sprite background;
    std::vector<sf::Text>::size_type selectedIndex;
};

#endif //MAINMENUSTATE_HPP