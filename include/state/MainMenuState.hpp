#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFGUI/SFGUI.hpp>
#include "state/State.hpp"

class MainMenuState : public State {

public:
    MainMenuState(StateStack& stack, Context context);

public:
    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event& event) override;

private:
    void onPlayButtonClick();
    void onExitButtonClick();

private:
    sf::Sprite background;
    sfg::Desktop desktop;
};

#endif //MAINMENUSTATE_HPP