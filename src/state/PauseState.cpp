#include "state/PauseState.hpp"
#include "util/Utility.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>

PauseState::PauseState(StateStack &stack, Context context)
        : State(stack, context),
          pauseText(),
          instructionText() {
    sf::Font &font = context.fontHolder->get(FontId::Main);

    sf::RenderWindow *window = getContext().window;
    sf::Vector2f viewSize = context.window->getView().getSize();

    pauseText.setFont(font);
    pauseText.setString("Paused");
    utility::centerOrigin(pauseText);
    pauseText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

    instructionText.setFont(font);
    instructionText.setString("Press backspace to return to the main menu");
    utility::centerOrigin(instructionText);
    instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw() {
    sf::RenderWindow *renderWindow = getContext().window;
    renderWindow->setView(renderWindow->getDefaultView());

    sf::RectangleShape overlay;
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    overlay.setSize(sf::Vector2f(renderWindow->getSize()));

    renderWindow->draw(overlay);
    renderWindow->draw(pauseText);
    renderWindow->draw(instructionText);
}

bool PauseState::update(sf::Time deltaTime) {
    return false;
}

bool PauseState::handleEvent(const sf::Event &event) {
    if (sf::Event::KeyPressed == event.type) {
        switch (event.key.code) {
            case sf::Keyboard::BackSpace:
                requestStateClear();
                requestStackPush(StateId::MainMenu);
                break;
            case sf::Keyboard::Escape:
                requestStackPop();
                break;
        }
    }

    return false;
}