#include "scene/TextNode.hpp"
#include "util/Utility.hpp"

TextNode::TextNode(const FontHolder& fonts, const std::string &text) {
    this->text.setFont(fonts.get(FontId::Main));
    this->text.setCharacterSize(20);
    setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(text, states);
}

void TextNode::setString(std::string text) {
    this->text.setString(text);
    utility::centerOrigin(this->text);
}