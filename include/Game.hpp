#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

#include "util/Resources.hpp"
#include "util/ResourceHolder.hpp"
#include "util/ext/Animation.hpp"
#include "util/ext/AnimatedSprite.hpp"
#include "World.hpp"
#include "Player.hpp"

class Game {
public:
    Game(sf::Vector2i screenDimensions);

//public:
//    void run();

//private:
//    static const unsigned int FrameRate;
//    static const sf::Time TimePerFrame;

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

private:
    sf::RenderWindow renderWindow;
    World world;
    Player player;
};

#endif //GAME_HPP