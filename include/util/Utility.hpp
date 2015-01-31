#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace sf {
    class Text;
    class Sprite;
}

namespace utility {
    void centerOrigin(sf::Sprite& sprite);
    void centerOrigin(sf::Text& text);
}

#endif //UTILITY_HPP