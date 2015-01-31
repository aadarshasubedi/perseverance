#ifndef STATE_HPP
#define STATE_HPP

#include "state/StateIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <util/Resources.hpp>

class StateStack;
class Player;

namespace sf {
    class RenderWindow;
}

class State {
public:
    using UniqueStatePtr = std::unique_ptr<State>;

public:
    struct Context {
        Context(sf::RenderWindow& window,
                TextureHolder& textureHolder,
                FontHolder& fontHolder,
                Player& player);

        sf::RenderWindow* window;
        TextureHolder* textureHolder;
        FontHolder* fontHolder;
        Player* player;
    };

public:
    explicit State(StateStack& stack, Context context);
    virtual ~State();

public:
    virtual void draw() = 0;
    virtual bool update(sf::Time deltaTime) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void requestStackPush(StateId stateId);
    void requestStackPop();
    void requestStateClear();
    Context getContext() const;
    int numberOfStatesOnStack() const;

private:
    StateStack* stack;
    Context context;
};

#endif //STATE_HPP