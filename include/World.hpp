#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <tmx/MapLoader.h>

#include "scene/Creature.hpp"
#include "util/Resources.hpp"
#include "util/ResourceHolder.hpp"
#include "scene/SceneNode.hpp"
#include "scene/CommandQueue.hpp"

class World : sf::NonCopyable {

public:
    explicit World(sf::RenderWindow& window);

public:
    void update(sf::Time deltaTime);
    void draw();
    CommandQueue& getCommandQueue();
    void resizeView(int width, int height);

private:
    void loadResources();
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
    TextureHolder textures;
    FontHolder fonts;
    sf::View view;
    SceneNode sceneGraph;
    std::array<SceneNode*, Layer::LayerCount> layers;
    sf::FloatRect bounds;
    Creature* hero;
    CommandQueue commandQueue;
    tmx::MapLoader overworldMapLoader;
};

#endif //WORLD_HPP