#include "Application.hpp"
#include "state/MainMenuState.hpp"
#include "state/TitleState.hpp"
#include "state/GameState.hpp"
#include "state/PauseState.hpp"
#include "state/LoadingState.hpp"

const unsigned int Application::FrameRate = 60;
const sf::Time Application::TimePerFrame = sf::seconds(1.f / (Application::FrameRate));

Application::Application(sf::Vector2i screenDimensions)
        : window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Perseverance"),
          textureHolder(),
          fontHolder(),
          player(),
          sfgui(),
          stateStack(State::Context(window, textureHolder, fontHolder, player)) {
    textureHolder.load(TextureId::TitleScreen, "resources/ui/title/lpc_home_cup.gif");
    fontHolder.load(FontId::Main, "resources/fonts/kenpixel.ttf");

    registerStates();

    stateStack.pushState(StateId::Title);

    //This is to handle mixing SFGUI OpenGL calls with SFML drawing
    window.resetGLStates();
}

void Application::run() {
    sf::Clock frameClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Time elapsedTime = frameClock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            if (stateStack.isEmpty()) {
                window.close();
            }
        }

        render();
    }
}

void Application::registerStates() {
    stateStack.registerState<TitleState>(StateId::Title);
    stateStack.registerState<MainMenuState>(StateId::MainMenu);
    stateStack.registerState<GameState>(StateId::Game);
    stateStack.registerState<PauseState>(StateId::Pause);
    stateStack.registerState<LoadingState>(StateId::Loading);
}

void Application::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        stateStack.handleEvent(event);

        if (sf::Event::Closed == event.type) {
            window.close();
        }
    }
}

void Application::update(sf::Time deltaTime) {
    stateStack.update(deltaTime);
}

void Application::render() {
    window.clear();
    stateStack.draw();
    sfgui.Display(window);
    window.display();
}