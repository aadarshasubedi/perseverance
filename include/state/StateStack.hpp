#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include "State.hpp"
#include "state/StateIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <vector>
#include <map>

class StateStack {
public:
    enum class Action {
        Push,
        Pop,
        Clear
    };

public:
    explicit StateStack(State::Context context);

public:
    template <typename T>
    void registerState(StateId stateId);

public:
    void update(sf::Time deltaTime);
    void draw();
    void handleEvent(const sf::Event& event);
    void pushState(StateId stateId);
    void popState();
    void clearStates();
    bool isEmpty() const;
    int numberOfStates() const;

private:
    State::UniqueStatePtr createState(StateId stateId);
    void applyPendingChanges();

private:
    struct PendingChange {
        explicit PendingChange(Action pendingAction, StateId stateId = StateId::None);

        Action action;
        StateId stateId;
    };

private:
    std::vector<State::UniqueStatePtr> stack;
    std::vector<PendingChange> pendingList;
    State::Context context;
    std::map<StateId, std::function<State::UniqueStatePtr()>> factories;
};

#include "inline/StateStack.inl"

#endif //STATESTACK_HPP