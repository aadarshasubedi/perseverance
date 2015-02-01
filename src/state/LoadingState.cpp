#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "state/LoadingState.hpp"
#include "state/StateStack.hpp"
#include "util/Utility.hpp"

LoadingState::LoadingState(StateStack &stack, Context context)
        : State(stack, context),
          loadingText(),
          progressBar(),
          progressBarBackground(),
          task() {
    sf::Font &font = context.fontHolder->get(FontId::Main);
    sf::Vector2f viewSize = context.window->getView().getSize();

    loadingText.setFont(font);
    loadingText.setString("Loading Resources");
    utility::centerOrigin(loadingText);
    loadingText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 50.f);

    progressBarBackground.setFillColor(sf::Color::White);
    progressBarBackground.setSize(sf::Vector2f(viewSize.x - 20, 10));
    progressBarBackground.setPosition(10, loadingText.getPosition().y + 40);

    progressBar.setFillColor(sf::Color::Red);
    progressBar.setSize(sf::Vector2f(200, 10));
    progressBar.setPosition(10, loadingText.getPosition().y + 40);

    setCompletion(0.f);

    task.execute();
}

void LoadingState::draw() {
    sf::RenderWindow *renderWindow = getContext().window;

    renderWindow->setView(renderWindow->getDefaultView());

    renderWindow->draw(loadingText);
    renderWindow->draw(progressBarBackground);
    renderWindow->draw(progressBar);
}

bool LoadingState::update(sf::Time deltaTime) {
    if (task.isComplete()) {
        requestStackPop();
        requestStackPush(StateId::Game);
    } else {
        setCompletion(task.getCompletion());
    }
    return false;
}

bool LoadingState::handleEvent(const sf::Event &event) {
    return false;
}

void LoadingState::setCompletion(float completionPercentage) {
    completionPercentage = std::min(1.f, completionPercentage);
    progressBar.setSize(sf::Vector2f(progressBarBackground.getSize().x * completionPercentage, progressBar.getSize().y));
}