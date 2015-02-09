#include "World.hpp"

World::World(sf::RenderWindow &windowParam)
        : window(windowParam),
          textures(),
          fonts(),
          view(windowParam.getDefaultView()),
          sceneGraph(),
          layers(),
          overworldMapLoader("resources/maps"),
          bounds(0.f, 0.f, view.getSize().x, view.getSize().y),
          hero(nullptr) {
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    loadResources();
    buildScene();

    overworldMapLoader.AddSearchPath("resources/maps/atlas");
    overworldMapLoader.Load("landing.tmx");
}

void World::update(sf::Time deltaTime) {
    hero->setVelocity(0.f, 0.f);

    while (!commandQueue.isEmpty()) {
        sceneGraph.onCommand(commandQueue.pop(), deltaTime);
    }

    sceneGraph.update(deltaTime);

    boundHero();
    view.setCenter(hero->getPosition());
    boundView();
}

void World::draw() {
    window.setView(view);
    window.draw(overworldMapLoader);
    window.draw(sceneGraph);
}

void World::loadResources() {
    textures.load(TextureId::Human, "resources/sprites/complete/male_default.png");
    textures.load(TextureId::Orc, "resources/sprites/complete/orc_default.png");

    fonts.load(FontId::Main, "resources/fonts/kenpixel.ttf");
}

void World::buildScene() {
    for (std::size_t i = 0; i < Layer::LayerCount; ++i) {
        SceneNode::SceneNodePtr layer(new SceneNode());
        layers[i] = layer.get();

        sceneGraph.attachChild(std::move(layer));
    }

    std::unique_ptr<Creature> heroNode(new Creature(CreatureType::Human, textures, fonts));
    hero = heroNode.get();
    layers[Layer::Foreground]->attachChild(std::move(heroNode));

    hero->move(window.getSize().x/2, window.getSize().y/2);
}

CommandQueue& World::getCommandQueue() {
    return commandQueue;
}

void World::resizeView(int width, int height) {
    view.setSize(width, height);
}

void World::boundHero() {
    sf::Vector2f heroPosition = hero->getPosition();
    sf::Vector2u mapSize = overworldMapLoader.GetMapSize();

    heroPosition.x = std::max(heroPosition.x, 0.0f);
    heroPosition.x = std::min(heroPosition.x, mapSize.x * 1.0f);

    heroPosition.y = std::max(heroPosition.y, 0.0f);
    heroPosition.y = std::min(heroPosition.y, mapSize.y * 1.0f);

    hero->setPosition(heroPosition);
}

void World::boundView() {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    sf::Vector2f upperLeft;
    upperLeft.x = viewCenter.x - (viewSize.x / 2.f);
    upperLeft.y = viewCenter.y - (viewSize.y / 2.f);

    sf::Vector2f boundUpperLeft = upperLeft;
    boundUpperLeft.x = std::max(boundUpperLeft.x, 0.f);
    boundUpperLeft.x = std::min(boundUpperLeft.x, (overworldMapLoader.GetMapSize().x * 1.f) - viewSize.x);

    boundUpperLeft.y = std::max(boundUpperLeft.y, 0.f);
    boundUpperLeft.y = std::min(boundUpperLeft.y, (overworldMapLoader.GetMapSize().y * 1.f) - viewSize.y);

    if (upperLeft.x != boundUpperLeft.x || upperLeft.y != boundUpperLeft.y) {
        sf::Vector2f newViewCenter;
        newViewCenter.x = boundUpperLeft.x + (viewSize.x / 2.f);
        newViewCenter.y = boundUpperLeft.y + (viewSize.y / 2.f);
        view.setCenter(newViewCenter);
    }
}