#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "ResourceHolder.hpp"

enum class TextureId {
    Hero,
    TitleScreen
};

enum class FontId {
    Main
};

//Forward Declarations
template<typename Resource, typename Identifier>
class ResourceHolder;

namespace sf {
    class Texture;
    class Font;
}

using TextureHolder = ResourceHolder<sf::Texture, TextureId>;
using FontHolder = ResourceHolder<sf::Font, FontId>;

#endif // RESOURCES_HPP