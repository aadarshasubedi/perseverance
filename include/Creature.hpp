#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "util/Entity.hpp"
#include "util/ext/Animation.hpp"
#include "util/ext/AnimatedSprite.hpp"
#include "util/Resources.hpp"
#include "CreatureCatalog.hpp"

#include <map>

class Creature : public Entity {

public:
    Creature(CreatureType type, const TextureHolder& textureHolder);

public:
    void setHeading(Heading heading);

public:
    virtual Category::Type getCategory() const override;

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void updateCurrent(sf::Time dt) override;

private:
    typedef std::unique_ptr<Animation> AnimationPtr;

private:
    AnimatedSprite sprite;
    Heading heading;
    std::map<Heading, AnimationPtr> walkingAnimations;
    std::map<Heading, AnimationPtr> standingAnimations;
    CreatureType type;
};

#endif //CREATURE_HPP