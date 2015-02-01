#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "state/State.hpp"
#include "state/ResourceLoaderTask.hpp"

class LoadingState : public State {

public:
    LoadingState(StateStack& stack, Context context);

public:
    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event& event) override;

private:
    void setCompletion(float completionPercentage);

private:
    sf::Text loadingText;
    sf::RectangleShape progressBar;
    sf::RectangleShape progressBarBackground;
    ResourceLoaderTask task; //This is a stub, should become an interface so different tasks
};

#endif //LOADINGSTATE_HPP