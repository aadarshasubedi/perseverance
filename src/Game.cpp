#include "Game.hpp"

const unsigned int Game::FrameRate = 60;
const float Game::PlayerSpeed = 90.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/(Game::FrameRate * 1.f));

Game::Game(sf::Vector2i screenDimensionsParam)
        : screenDimensions(screenDimensionsParam),
          renderWindow(sf::VideoMode(screenDimensionsParam.x, screenDimensionsParam.y), "Perseverance"),
          overworldView(sf::Vector2f(400, 300), sf::Vector2f(screenDimensionsParam.x, screenDimensionsParam.y)),
          overworldMapLoader("resources/maps"),
          movement(0.f, 0.f),
          noKeyWasPressed(false){
    renderWindow.setFramerateLimit(60);

    textureCache.load(Textures::Hero, "resources/sprites/complete/male_default.png");

    overworldView.setViewport(sf::FloatRect(0, 0, 1, 1));

    renderWindow.setView(overworldView);

    overworldMapLoader.AddSearchPath("resources/maps/atlas");
    overworldMapLoader.Load("landing.tmx");

    walkingAnimationUp.setSpriteSheet(textureCache.get(Textures::Hero));
    walkingAnimationUp.addFrame(sf::IntRect(64, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(128, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(192, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(256, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(320, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(384, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(448, 512, 64, 64));
    walkingAnimationUp.addFrame(sf::IntRect(512, 512, 64, 64));

    standingAnimationUp.setSpriteSheet(textureCache.get(Textures::Hero));
    standingAnimationUp.addFrame(sf::IntRect(0, 512, 64, 64));

    walkingAnimationLeft.setSpriteSheet(textureCache.get(Textures::Hero));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(128, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(192, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(256, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(320, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(384, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(448, 576, 64, 64));
    walkingAnimationLeft.addFrame(sf::IntRect(512, 576, 64, 64));

    standingAnimationLeft.setSpriteSheet(textureCache.get(Textures::Hero));
    standingAnimationLeft.addFrame(sf::IntRect(0, 576, 64, 64));

    walkingAnimationDown.setSpriteSheet(textureCache.get(Textures::Hero));
    walkingAnimationDown.addFrame(sf::IntRect(64, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(128, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(192, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(256, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(320, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(384, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(448, 640, 64, 64));
    walkingAnimationDown.addFrame(sf::IntRect(512, 640, 64, 64));

    standingAnimationDown.setSpriteSheet(textureCache.get(Textures::Hero));
    standingAnimationDown.addFrame(sf::IntRect(0, 640, 64, 64));

    walkingAnimationRight.setSpriteSheet(textureCache.get(Textures::Hero));
    walkingAnimationRight.addFrame(sf::IntRect(64, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(128, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(192, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(256, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(320, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(384, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(448, 704, 64, 64));
    walkingAnimationRight.addFrame(sf::IntRect(512, 704, 64, 64));

    standingAnimationRight.setSpriteSheet(textureCache.get(Textures::Hero));
    standingAnimationRight.addFrame(sf::IntRect(0, 704, 64, 64));

    currentAnimation = &standingAnimationDown;
    lastStandingHeadingAnimation = &standingAnimationDown;

    hero.setFrameTime(sf::seconds(0.2));
    hero.pause();
    hero.setLooped(false);
    hero.setPosition(sf::Vector2f(screenDimensions / 2));
}

void Game::run() {
    sf::Clock frameClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (renderWindow.isOpen()) {
        processEvents();

        sf::Time elapsedTime = frameClock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (renderWindow.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            renderWindow.close();
        } else if (sf::Event::KeyPressed == event.type
                && sf::Keyboard::Escape == event.key.code) {
            renderWindow.close();
        } else if (sf::Event::Resized == event.type) {
            overworldView.setSize(event.size.width, event.size.height);
        }
    }

    movement.x = 0.f;
    movement.y = 0.f;
    noKeyWasPressed = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        currentAnimation = &walkingAnimationUp;
        lastStandingHeadingAnimation = &standingAnimationUp;
        movement.y -= PlayerSpeed;
        noKeyWasPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        currentAnimation = &walkingAnimationDown;
        lastStandingHeadingAnimation = &standingAnimationDown;
        movement.y += PlayerSpeed;
        noKeyWasPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        currentAnimation = &walkingAnimationLeft;
        lastStandingHeadingAnimation = &standingAnimationLeft;
        movement.x -= PlayerSpeed;
        noKeyWasPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        currentAnimation = &walkingAnimationRight;
        lastStandingHeadingAnimation = &standingAnimationRight;
        movement.x += PlayerSpeed;
        noKeyWasPressed = false;
    }
}

void Game::update(sf::Time deltaTime) {
        //If no key, use a standing animation that reflects that most recent direction traveled.
        if (noKeyWasPressed) {
            currentAnimation = lastStandingHeadingAnimation;
        }

        hero.play(*currentAnimation);
        hero.move(movement * deltaTime.asSeconds());

        //Camera tracks sprite
        overworldView.setCenter(hero.getPosition());

        if (noKeyWasPressed) {
            hero.stop();
        }

        hero.update(deltaTime);
}

void Game::render() {
    renderWindow.clear();
    renderWindow.setView(overworldView);
    overworldMapLoader.Draw(renderWindow, 0, true);
    overworldMapLoader.Draw(renderWindow, 1, true);
    renderWindow.draw(hero);
    overworldMapLoader.Draw(renderWindow, 2, true);
    renderWindow.display();
}