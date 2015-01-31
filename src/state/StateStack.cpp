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
    for (auto itr = stack.rbegin(); itr != stack.rend(); itr++) {
        if (!(*itr)->handleEvent(event)) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::update(sf::Time deltaTime) {
    for (auto itr = stack.rbegin(); itr != stack.rend(); itr++) {
        if (!(*itr)->update(deltaTime)) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::draw() {
    for (auto itr = stack.begin(); itr != stack.end(); itr++) {
        (*itr)->draw();
    }
//    for (const State::UniqueStatePtr &state : stack) {
//        state->draw();
//    }
}

void StateStack::applyPendingChanges() {
    for (auto &pendingChange : pendingList) {
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

void StateStack::popState() {
    pendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates() {
    pendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const {
    return stack.empty();
}

int StateStack::numberOfStates() const {
    return stack.size();
}
