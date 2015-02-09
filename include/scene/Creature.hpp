#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "scene/Entity.hpp"
#include "util/ext/Animation.hpp"
#include "util/ext/AnimatedSprite.hpp"
#include "util/Resources.hpp"
#include "scene/CreatureCatalog.hpp"
#include "scene/TextNode.hpp"

#include <map>

class Creature : public Entity {

public:
    Creature(CreatureType type, const TextureHolder& textures, const FontHolder& fonts);

public:
    void setHeading(Heading heading);
    float getSpeed() const;

public:
    virtual Category::Type getCategory() const override;

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void updateCurrent(sf::Time dt) override;

private:
    void updateHealthText();

private:
    using AnimationPtr = std::unique_ptr<Animation>;

private:
    AnimatedSprite sprite;
    Heading heading;
    std::map<Heading, AnimationPtr> walkingAnimations;
    std::map<Heading, AnimationPtr> standingAnimations;
    CreatureType type;
    TextNode* healthDisplay;
    float speed;
};

#endif //CREATURE_HPPde