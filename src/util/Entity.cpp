#include "util/Entity.hpp"

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
