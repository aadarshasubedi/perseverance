#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include "Resources.hpp"
#include "ResourceHolder.hpp"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

class Game {
public:
    Game(sf::Vector2i screenDimensions);

public:
    void run();

private:
    static const unsigned int FrameRate;
    static const sf::Time TimePerFrame;
    static const float PlayerSpeed;

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

private:
    sf::RenderWindow renderWindow;
    sf::View overworldView;
    sf::Vector2i screenDimensions;
    tmx::MapLoader overworldMapLoader;
    ResourceHolder<sf::Texture, Textures::Id> textureCache;
    Animation walkingAnimationUp;
    Animation standingAnimationUp;
    Animation walkingAnimationLeft;
    Animation standingAnimationLeft;
    Animation walkingAnimationDown;
    Animation standingAnimationDown;
    Animation walkingAnimationRight;
    Animation standingAnimationRight;
    Animation* currentAnimation;
    Animation* lastStandingHeadingAnimation;
    AnimatedSprite hero;
    sf::Vector2f movement;
    bool noKeyWasPressed;
};

#endif //GAME_HPP