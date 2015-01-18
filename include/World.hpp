#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <tmx/MapLoader.h>

#include "Resources.hpp"
#include "ResourceHolder.hpp"
#include "SceneNode.hpp"
#include "Hero.hpp"
#include "CommandQueue.hpp"

class World : sf::NonCopyable {

public:
    World(sf::RenderWindow& window);

public:
    void update(sf::Time deltaTime);
    void draw();
    CommandQueue& getCommandQueue();
    void resizeView(int width, int height);

private:
    void loadTextures();
    void buildScene();

private:
    enum Layer : unsigned int {
        Background,
        Foreground,
        LayerCount
    };

private:
    void boundHero();
    void boundView();

private:
    sf::RenderWindow& window;
    sf::View view;
    TextureHolder textureHolder;
    SceneNode sceneGraph;
    std::array<SceneNode*, Layer::LayerCount> layers;
    sf::FloatRect bounds;
    Hero* hero;
    CommandQueue commandQueue;
    tmx::MapLoader overworldMapLoader;
};

#endif //WORLD_HPP