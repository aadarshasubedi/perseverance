#ifndef HERO_HPP
#define HERO_HPP

#include "util/Entity.hpp"
#include "util/ext/Animation.hpp"
#include "util/ext/AnimatedSprite.hpp"
#include "util/Resources.hpp"

#include <map>

class Hero : public Entity {

public:
    enum class Heading : unsigned int {
        North = 0x01,
        West = 0x02,
        South = 0x03,
        East = 0x04
    };

public:
    Hero(const TextureHolder& textureHolder);

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
};

#endif //HERO_HPP