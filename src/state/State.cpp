#include "state/State.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

State::Context::Context(sf::RenderWindow &window, TextureHolder &textureHolder, FontHolder &fontHolder, Player &player)
        : window(&window),
          textureHolder(&textureHolder),
          fontHolder(&fontHolder),
          player(&player) {
}

State::State(StateStack &stack, State::Context context)
        : stack(&stack), context(context) {

}

State::~State() {

}


State::Context State::getContext() const{
    return context;
}