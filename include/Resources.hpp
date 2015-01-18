#ifndef RESOURCES_HPP
#define RESOURCES_HPP

enum class TextureId {
    Hero
};

//Forward Declarations
template<typename Resource, typename Identifier>
class ResourceHolder;

namespace sf {
    class Texture;
}

typedef ResourceHolder<sf::Texture, TextureId> TextureHolder;

#endif // RESOURCES_HPP