#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "state/StateStack.hpp"
#include "state/MainMenuState.hpp"
#include "util/Utility.hpp"

MainMenuState::MainMenuState(StateStack &stack, Context context)
        : State(stack, context),
          desktop() {
    sf::Texture &texture = context.textureHolder->get(TextureId::TitleScreen);
    sf::Font &font = context.fontHolder->get(FontId::Main);

    background.setTexture(context.textureHolder->get(TextureId::TitleScreen));
    sf::RenderWindow *window = getContext().window;
    sf::Vector2u windowSize = window->getSize();
    sf::Vector2u spriteTextureSize = background.getTexture()->getSize();
    background.setScale(float(windowSize.x) / spriteTextureSize.x, float(windowSize.y) / spriteTextureSize.y);

    auto playButton = sfg::Button::Create("Play");
    playButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuState::onPlayButtonClick, this));

    auto exitButton = sfg::Button::Create("Exit");
    exitButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuState::onExitButtonClick, this));

    auto alignment = sfg::Alignment::Create();
    alignment->SetScale(sf::Vector2f(.0f, .0f));
    alignment->SetAlignment(sf::Vector2f(.5f, .5f));

    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
    box->Pack(playButton, false, false);
    box->Pack(exitButton, false, false);
    box->SetRequisition(context.window->getView().getSize() / 4.f);

    alignment->Add(box);

    auto guiWindow = sfg::Window::Create(sfg::Window::NO_STYLE);
    guiWindow->Add(alignment);
    guiWindow->SetRequisition(context.window->getView().getSize());

    desktop.Add(guiWindow);
}

void MainMenuState::draw() {
    sf::RenderWindow *renderWindow = getContext().window;
    renderWindow->draw(background);
}

bool MainMenuState::update(sf::Time deltaTime) {
    desktop.Update(deltaTime.asSeconds());
    return false;
}

bool MainMenuState::handleEvent(const sf::Event &event) {
    desktop.HandleEvent(event);
    return false;
}

void MainMenuState::onPlayButtonClick() {
    requestStackPop();
    requestStackPush(StateId::Game);
}

void MainMenuState::onExitButtonClick() {
    //Main Menu should be the only state on the stack.
    assert(1 == numberOfStatesOnStack());
    requestStackPop();
}