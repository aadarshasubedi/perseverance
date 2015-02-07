#include "Creature.hpp"

#include <cassert>
#include <SFML/Graphics/RectangleShape.hpp>

CreatureCatalogUptr creatureCatalog = initializeCreatureData();

Creature::Creature(CreatureType type, const TextureHolder &textureHolder)
        : Entity{},
          type(type),
          heading(Heading::South) {

    auto creatureData = creatureCatalog->getCreature(type);

    assert(nullptr != creatureData);

    AnimationPtr walkingAnimationNorth(new Animation());
    AnimationPtr standingAnimationNorth(new Animation());

    AnimationPtr walkingAnimationWest(new Animation());
    AnimationPtr standingAnimationWest(new Animation());

    AnimationPtr walkingAnimationSouth(new Animation());
    AnimationPtr standingAnimationSouth(new Animation());

    AnimationPtr walkingAnimationEast(new Animation());
    AnimationPtr standingAnimationEast(new Animation());

    setHitPoints(creatureData->hitPoints);

    walkingAnimationNorth->setSpriteSheet(textureHolder.get(creatureData->textureId));
    standingAnimationNorth->setSpriteSheet(textureHolder.get(creatureData->textureId));

    walkingAnimationWest->setSpriteSheet(textureHolder.get(creatureData->textureId));
    standingAnimationWest->setSpriteSheet(textureHolder.get(creatureData->textureId));

    walkingAnimationSouth->setSpriteSheet(textureHolder.get(creatureData->textureId));
    standingAnimationSouth->setSpriteSheet(textureHolder.get(creatureData->textureId));

    walkingAnimationEast->setSpriteSheet(textureHolder.get(creatureData->textureId));
    standingAnimationEast->setSpriteSheet(textureHolder.get(creatureData->textureId));

    for (auto &frame : creatureData->walkingFrames) {
        switch (frame.heading) {
            case Heading::North:
                walkingAnimationNorth->addFrame(frame.frame);
                break;
            case Heading::West:
                walkingAnimationWest->addFrame(frame.frame);
                break;
            case Heading::South:
                walkingAnimationSouth->addFrame(frame.frame);
                break;
            case Heading::East:
                walkingAnimationEast->addFrame(frame.frame);
                break;
            default:
                assert(false);
        }
    }

    for (auto &frame : creatureData->standingFrames) {
        switch (frame.heading) {
            case Heading::North:
                standingAnimationNorth->addFrame(frame.frame);
                break;
            case Heading::West:
                standingAnimationWest->addFrame(frame.frame);
                break;
            case Heading::South:
                standingAnimationSouth->addFrame(frame.frame);
                break;
            case Heading::East:
                standingAnimationEast->addFrame(frame.frame);
                break;
            default:
                assert(false);
        }
    }

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

void Creature::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);

    static sf::Vector2f size(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
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

void Creature::updateCurrent(sf::Time dt) {
    if (getVelocity().x != 0.f || getVelocity().y != 0.f) {
        sprite.play(*walkingAnimations[heading].get());
        move(getVelocity() * dt.asSeconds());
    } else {
        sprite.play(*standingAnimations[heading].get());
        sprite.stop();
    }

    sprite.update(dt);
}

Category::Type Creature::getCategory() const {
    return Category::Hero;
}

void Creature::setHeading(Heading heading) {
    this->heading = heading;
}