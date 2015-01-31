#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "state/TitleState.hpp"

TitleState::TitleState(StateStack &stack, Context context)
        : State(stack, context),
          background() {
    background.setTexture(context.textureHolder->get(TextureId::TitleScreen));
    sf::RenderWindow *window = getContext().window;
    sf::Vector2u windowSize = window->getSize();
    sf::Vector2u spriteTextureSize = background.getTexture()->getSize();
    background.setScale(float(windowSize.x) / spriteTextureSize.x, float(windowSize.y) / spriteTextureSize.y);
}

void TitleState::draw() {
    sf::RenderWindow *renderWindow = getContext().window;
    renderWindow->draw(background);
}

bool TitleState::update(sf::Time deltaTime) {
    return false;
}

bool TitleState::handleEvent(const sf::Event &event) {
    if (sf::Event::KeyPressed == event.type) {
        requestStackPop();
        requestStackPush(StateId::MainMenu);
    }
    return false;
}