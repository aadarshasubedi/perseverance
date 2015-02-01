#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "state/StateStack.hpp"
#include "state/MainMenuState.hpp"
#include "util/Utility.hpp"

MainMenuState::MainMenuState(StateStack &stack, Context context)
        : State(stack, context),
          options(),
          selectedIndex(0) {
    sf::Texture &texture = context.textureHolder->get(TextureId::TitleScreen);
    sf::Font &font = context.fontHolder->get(FontId::Main);

    background.setTexture(context.textureHolder->get(TextureId::TitleScreen));
    sf::RenderWindow *window = getContext().window;
    sf::Vector2u windowSize = window->getSize();
    sf::Vector2u spriteTextureSize = background.getTexture()->getSize();
    background.setScale(float(windowSize.x) / spriteTextureSize.x, float(windowSize.y) / spriteTextureSize.y);

    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    utility::centerOrigin(playOption);
    playOption.setPosition(window->getView().getSize() / 2.f);
    options.push_back(playOption);

    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setString("Exit");
    utility::centerOrigin(exitOption);
    exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
    options.push_back(exitOption);

    updateTextColor();
}

void MainMenuState::draw() {
    sf::RenderWindow *renderWindow = getContext().window;
    renderWindow->draw(background);

    for (auto &option : options) {
        renderWindow->draw(option);
    }
}

bool MainMenuState::update(sf::Time deltaTime) {
    return false;
}

bool MainMenuState::handleEvent(const sf::Event &event) {
    if (sf::Event::KeyPressed == event.type) {
        if (sf::Keyboard::Return == event.key.code) {
            switch (selectedIndex) {
                case Play:
                    requestStackPop();
                    requestStackPush(StateId::Game);
                    break;
                case Exit:
                    //Main Menu should be the only state on the stack.
                    assert(1 == numberOfStatesOnStack());
                    requestStackPop();
                    break;
            }
        } else if (sf::Keyboard::Up == event.key.code) {
            if (selectedIndex > 0) {
                selectedIndex--;
            }
        } else if (sf::Keyboard::Down == event.key.code) {
            if (selectedIndex < options.size() - 1) {
                selectedIndex++;
            }
        }

        updateTextColor();
    }
    return false;
}

void MainMenuState::updateTextColor() {
    if (!options.empty()) {
        for (auto &option : options) {
            option.setColor(sf::Color::White);
        }

        options[selectedIndex].setColor(sf::Color::Red);
    }
}