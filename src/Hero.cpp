#include "Hero.hpp"
#include "util/ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

Hero::Hero(const TextureHolder& textureHolder)
        : heading(Heading::South) {
    AnimationPtr walkingAnimationNorth(new Animation());
    walkingAnimationNorth->setSpriteSheet(textureHolder.get(TextureId::Hero));
    walkingAnimationNorth->addFrame(sf::IntRect(64, 512, 64, 64));
    walkingAnimationNorth->addFrame(sf::IntRect(128, 512, 64, 64));
    walkingAnimationNorth->addFrame(sf::IntRect(192, 512, 64, 64));
    walkingAnimationNorth->addFrame(sf::IntRect(256, 512, 64, 64));
    walkingAnimationNorth->addFrame(sf::IntRect(320, 512, 64, 64));
    walkingAnimationNorth->addFrame(sf::IntRect(384, 512, 64, 64));
    walkingAnimationNorth->addFrame(sf::IntRect(448, 512, 64, 64));
    walkingAnimationNorth->addFrame(sf::IntRect(512, 512, 64, 64));

    AnimationPtr standingAnimationNorth(new Animation());
    standingAnimationNorth->setSpriteSheet(textureHolder.get(TextureId::Hero));
    standingAnimationNorth->addFrame(sf::IntRect(0, 512, 64, 64));

    AnimationPtr walkingAnimationWest(new Animation());
    walkingAnimationWest->setSpriteSheet(textureHolder.get(TextureId::Hero));
    walkingAnimationWest->addFrame(sf::IntRect(64, 576, 64, 64));
    walkingAnimationWest->addFrame(sf::IntRect(128, 576, 64, 64));
    walkingAnimationWest->addFrame(sf::IntRect(192, 576, 64, 64));
    walkingAnimationWest->addFrame(sf::IntRect(256, 576, 64, 64));
    walkingAnimationWest->addFrame(sf::IntRect(320, 576, 64, 64));
    walkingAnimationWest->addFrame(sf::IntRect(384, 576, 64, 64));
    walkingAnimationWest->addFrame(sf::IntRect(448, 576, 64, 64));
    walkingAnimationWest->addFrame(sf::IntRect(512, 576, 64, 64));

    AnimationPtr standingAnimationWest(new Animation());
    standingAnimationWest->setSpriteSheet(textureHolder.get(TextureId::Hero));
    standingAnimationWest->addFrame(sf::IntRect(0, 576, 64, 64));

    AnimationPtr walkingAnimationSouth(new Animation());
    walkingAnimationSouth->setSpriteSheet(textureHolder.get(TextureId::Hero));
    walkingAnimationSouth->addFrame(sf::IntRect(64, 640, 64, 64));
    walkingAnimationSouth->addFrame(sf::IntRect(128, 640, 64, 64));
    walkingAnimationSouth->addFrame(sf::IntRect(192, 640, 64, 64));
    walkingAnimationSouth->addFrame(sf::IntRect(256, 640, 64, 64));
    walkingAnimationSouth->addFrame(sf::IntRect(320, 640, 64, 64));
    walkingAnimationSouth->addFrame(sf::IntRect(384, 640, 64, 64));
    walkingAnimationSouth->addFrame(sf::IntRect(448, 640, 64, 64));
    walkingAnimationSouth->addFrame(sf::IntRect(512, 640, 64, 64));

    AnimationPtr standingAnimationSouth(new Animation());
    standingAnimationSouth->setSpriteSheet(textureHolder.get(TextureId::Hero));
    standingAnimationSouth->addFrame(sf::IntRect(0, 640, 64, 64));

    AnimationPtr walkingAnimationEast(new Animation());
    walkingAnimationEast->setSpriteSheet(textureHolder.get(TextureId::Hero));
    walkingAnimationEast->addFrame(sf::IntRect(64, 704, 64, 64));
    walkingAnimationEast->addFrame(sf::IntRect(128, 704, 64, 64));
    walkingAnimationEast->addFrame(sf::IntRect(192, 704, 64, 64));
    walkingAnimationEast->addFrame(sf::IntRect(256, 704, 64, 64));
    walkingAnimationEast->addFrame(sf::IntRect(320, 704, 64, 64));
    walkingAnimationEast->addFrame(sf::IntRect(384, 704, 64, 64));
    walkingAnimationEast->addFrame(sf::IntRect(448, 704, 64, 64));
    walkingAnimationEast->addFrame(sf::IntRect(512, 704, 64, 64));

    AnimationPtr standingAnimationEast(new Animation());
    standingAnimationEast->setSpriteSheet(textureHolder.get(TextureId::Hero));
    standingAnimationEast->addFrame(sf::IntRect(0, 704, 64, 64));

    walkingAnimations[Heading::North] = std::move(walkingAnimationNorth);
    walkingAnimations[Heading::West] = std::move(walkingAnimationWest);
    walkingAnimations[Heading::South] = std::move(walkingAnimationSouth);
    walkingAnimations[Heading::East] = std::move(walkingAnimationEast);

    standingAnimations[Heading::North] = std::move(standingAnimationNorth);
    standingAnimations[Heading::West] = std::move(standingAnimationWest);
    standingAnimations[Heading::South] = std::move(standingAnimationSouth);
    standingAnimations[Heading::East] = std::move(standingAnimationEast);


    sprite.setFrameTime(sf::seconds(0.2));
    sprite.setLooped(false);
    sprite.play(*standingAnimations[Heading::South]);
    sprite.pause();

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Hero::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);

    static sf::Vector2f size (sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    static sf::RectangleShape boundingBox(size);
    boundingBox.setFillColor(sf::Color::Transparent);
    boundingBox.setOutlineThickness(2);
    boundingBox.setOutlineColor(sf::Color::Red);

    static sf::Vector2f position;

    position.x = sprite.getPosition().x - sprite.getOrigin().x;
    position.y = sprite.getPosition().y - sprite.getOrigin().y;

    boundingBox.setPosition(position);
    target.draw(boundingBox, states);
}

void Hero::updateCurrent(sf::Time dt) {
    if (getVelocity().x != 0.f || getVelocity().y != 0.f) {
        sprite.play(*walkingAnimations[heading].get());
        move(getVelocity() * dt.asSeconds());
    } else {
        sprite.play(*standingAnimations[heading].get());
        sprite.stop();
    }

    sprite.update(dt);
}

Category::Type Hero::getCategory() const {
    return Category::Hero;
}

void Hero::setHeading(Heading heading) {
    this->heading = heading;
}