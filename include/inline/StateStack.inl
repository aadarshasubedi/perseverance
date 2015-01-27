template <typename T>
void StateStack::registerState(StateId stateId) {
    factories[stateId] = [this] () {
        return State::UniqueStatePtr(new T(*this, context));
    };
}