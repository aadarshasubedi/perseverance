#include "state/StateStack.hpp"

#include <cassert>


StateStack::PendingChange::PendingChange(Action pendingAction, StateId stateId)
        : action(pendingAction),
          stateId(stateId) {

}

StateStack::StateStack(State::Context context)
        : context(context) {
}

State::UniqueStatePtr StateStack::createState(StateId stateId) {
    auto factory = factories.find(stateId);
    assert(factories.end() != factory);
    return factory->second();
}

void StateStack::handleEvent(const sf::Event &event) {
    for (const State::UniqueStatePtr &state : stack) {
        if (!state->handleEvent(event)) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::update(sf::Time deltaTime) {
    for (const State::UniqueStatePtr &state : stack) {
        if (!state->update(deltaTime)) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::draw() {
    for (const State::UniqueStatePtr &state : stack) {
        state->draw();
    }
}

void StateStack::applyPendingChanges() {
    for (auto& pendingChange : pendingList) {
        switch (pendingChange.action) {
            case Action::Pop:
                stack.pop_back();
                break;
            case Action::Push:
                stack.push_back(createState(pendingChange.stateId));
                break;
            case Action::Clear:
                stack.clear();
                break;
        }
    }

    pendingList.clear();
}

void StateStack::pushState(StateId stateId) {
    pendingList.push_back(PendingChange(Action::Push, stateId));
}

bool StateStack::isEmpty() const {
    return stack.empty();
}