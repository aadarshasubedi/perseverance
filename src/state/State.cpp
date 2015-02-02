#include "state/State.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <state/StateStack.hpp>

State::Context::Context(sf::RenderWindow &window,
        TextureHolder &textureHolder,
        FontHolder &fontHolder,
        Player &player)
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

void State::requestStackPop() {
    stack->popState();
}

void State::requestStackPush(StateId stateId) {
    stack->pushState(stateId);
}

void State::requestStateClear() {
    stack->clearStates();
}

State::Context State::getContext() const {
    return context;
}

int State::numberOfStatesOnStack() const {
    return stack->numberOfStates();
}