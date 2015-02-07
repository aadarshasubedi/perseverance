#include "util/Entity.hpp"
#include <cassert>

Entity::Entity()
        : SceneNode{} {
}

void Entity::setVelocity(sf::Vector2f velocity) {
    this->velocity = velocity;
}

void Entity::setVelocity(float velocityX, float velocityY) {
    this->velocity.x = velocityX;
    this->velocity.y = velocityY;
}

sf::Vector2f Entity::getVelocity() const {
    return velocity;
}

void Entity::updateCurrent(sf::Time dt) {
    move(velocity * dt.asSeconds());
}

void Entity::heal(int hitPoints) {
    assert(hitPoints > 0);
    this->hitPoints += hitPoints;
}

void Entity::hurt(int hitPoints) {
    assert(hitPoints > 0);
    this->hitPoints -= hitPoints;
}

void Entity::kill() {
    hitPoints = 0;
}

int Entity::getHitPoints() const {
    return hitPoints;
}

bool Entity::isAlive() const {
    return hitPoints <= 0;
}

void Entity::setHitPoints(int hitPoints) {
    this->hitPoints = hitPoints;
}