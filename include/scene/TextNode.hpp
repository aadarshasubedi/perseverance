#ifndef TEXTNODE_HPP
#define TEXTNODE_HPP

#include <SFML/Graphics/Text.hpp>
#include "scene/SceneNode.hpp"
#include "util/Resources.hpp"

class TextNode : public SceneNode {
public:
    explicit TextNode(const FontHolder& fonts, const std::string& text);

public:
    void setString(std::string text);

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Text text;
};

#endif //TEXTNODE_HPP