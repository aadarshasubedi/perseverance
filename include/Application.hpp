#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "util/Resources.hpp"
#include "state/StateStack.hpp"
#include "Player.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

class Application {
public:
    explicit Application(sf::Vector2i screenDimensions);

public:
    void run();
    void registerStates();
    void processInput();
    void update(sf::Time deltaTime);
    void render();

private:
    static const unsigned int FrameRate;
    static const sf::Time TimePerFrame;

private:
    StateStack stateStack;
    sf::RenderWindow window;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    Player player;
};

#endif //APPLICATION_HPP