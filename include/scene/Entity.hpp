#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/System/Vector2.hpp>
#include "scene/SceneNode.hpp"

class Entity : public SceneNode {
public:
    explicit Entity();

public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float velocityX, float velocityY);
    sf::Vector2f getVelocity() const;
    void heal(int hitPoints);
    void hurt(int hitPoints);
    void kill();
    int getHitPoints() const;
    bool isAlive() const;

private:
    virtual void updateCurrent(sf::Time dt) override;

protected:
    void setHitPoints(int hitPoints);

private:
    int hitPoints;
    sf::Vector2f velocity;
};

#endif //ENTITY_HPP