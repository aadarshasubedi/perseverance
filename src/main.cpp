#include "config.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include <Animation.hpp>
#include <AnimatedSprite.hpp>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Version " << perseverance_VERSION_MAJOR << "." << perseverance_VERSION_MINOR << endl;

    sf::Vector2i screenDimensions(800, 600);

    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Perseverance");
    window.setFramerateLimit(60);

    //Main view
    sf::View overworldView(sf::Vector2f(400, 300), sf::Vector2f(screenDimensions.x, screenDimensions.y));
      overworldView.setViewport(sf::FloatRect(0, 0, 1, 1));

    //Map loading
    tmx::MapLoader ml("resources/maps");
    ml.AddSearchPath("resources/maps/atlas");
    ml.Load("landing.tmx");

    sf::Texture spriteSheet;
    if (!spriteSheet.loadFromFile("resources/sprites/complete/male_default.png")) {
        return -1;
    }

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(spriteSheet);
    walkingAnimationUp.addFrame(sf::IntRect(64, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(128, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(192, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(256, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(320, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(384, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(448, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(512, 512, 64, 64));

    Animation standingAnimationUp;
    standingAnimationUp.setSpriteSheet(spriteSheet);
    standingAnimationUp.addFrame(sf::IntRect(0, 512, 64, 64));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(spriteSheet);
    walkingAnimationLeft.addFrame(sf::IntRect(64, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(128, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(192, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(256, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(320, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(384, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(448, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(512, 576, 64, 64));

    Animation standingAnimationLeft;
    standingAnimationLeft.setSpriteSheet(spriteSheet);
    standingAnimationLeft.addFrame(sf::IntRect(0, 576, 64, 64));

    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(spriteSheet);
    walkingAnimationDown.addFrame(sf::IntRect(64, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(128, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(192, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(256, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(320, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(384, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(448, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(512, 640, 64, 64));

    Animation standingAnimationDown;
    standingAnimationDown.setSpriteSheet(spriteSheet);
    standingAnimationDown.addFrame(sf::IntRect(0, 640, 64, 64));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(spriteSheet);
    walkingAnimationRight.addFrame(sf::IntRect(64, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(128, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(192, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(256, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(320, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(384, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(448, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(512, 704, 64, 64));

    Animation standingAnimationRight;
    standingAnimationRight.setSpriteSheet(spriteSheet);
    standingAnimationRight.addFrame(sf::IntRect(0, 704, 64, 64));

    Animation* currentAnimation = &standingAnimationDown;
    Animation* lastStandingHeadingAnimation = &standingAnimationDown;

    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    float speed = 90.f;
    bool noKeyWasPressed = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                window.close();
            } else if (sf::Event::KeyPressed == event.type
                    && sf::Keyboard::Escape == event.key.code) {
                window.close();
            } else if (sf::Event::Resized == event.type) {
                overworldView.setSize(event.size.width, event.size.height);
            }
        }
        sf::Time frameTime = frameClock.restart();

        sf::Vector2f movement(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            currentAnimation = &walkingAnimationUp;
            lastStandingHeadingAnimation = &standingAnimationUp;
            movement.y -= speed;
            noKeyWasPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            currentAnimation = &walkingAnimationDown;
            lastStandingHeadingAnimation = &standingAnimationDown;
            movement.y += speed;
            noKeyWasPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            currentAnimation = &walkingAnimationLeft;
            lastStandingHeadingAnimation = &standingAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            currentAnimation = &walkingAnimationRight;
            lastStandingHeadingAnimation = &standingAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
        }

        //If no key, use a standing animation that reflects that most recent direction traveled.
        if (noKeyWasPressed) {
            currentAnimation = lastStandingHeadingAnimation;
        }

        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());

        //Camera tracks sprite
        overworldView.setCenter(animatedSprite.getPosition());

        if (noKeyWasPressed) {
            animatedSprite.stop();
        }

        noKeyWasPressed = true;

        animatedSprite.update(frameTime);

        window.clear();
        window.setView(overworldView);
        ml.Draw(window, 0, true);
        ml.Draw(window, 1, true);
        window.draw(animatedSprite);
        ml.Draw(window, 2, true);
        window.display();
    }
}
