#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/System/Vector2.hpp>
#include "SceneNode.hpp"

class Entity : public SceneNode {
public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float velocityX, float velocityY);
    sf::Vector2f getVelocity() const;

private:
    virtual void updateCurrent(sf::Time dt) override;

private:
    sf::Vector2f velocity;
};

#endif //ENTITY_HPP