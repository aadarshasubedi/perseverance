#include "scene/SceneNode.hpp"
#include "scene/Command.hpp"

#include <cassert>

SceneNode::SceneNode() :
        children(),
        parent(nullptr) {
}

void SceneNode::attachChild(SceneNodePtr sceneNode) {
    sceneNode->parent = this;

    //Assume sole ownership of the scene node
    children.push_back(std::move(sceneNode));
}

SceneNode::SceneNodePtr SceneNode::detachChild(const SceneNode &sceneNode) {
    auto found = std::find_if(children.begin(), children.end(),
            //Algorithm checks equality via address.
            [&](SceneNodePtr &snp) -> bool {
                return snp.get() == &sceneNode;
            });

    assert(found != children.end());

    SceneNodePtr foundNode = std::move(*found);
    foundNode->parent = nullptr;
    children.erase(found);

    return foundNode;
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

}

void SceneNode::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const SceneNodePtr &child : children) {
        child->draw(target, states);
    }
}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt) {

}

void SceneNode::updateChildren(sf::Time dt) {
    for (const SceneNodePtr &child : children) {
        child->update(dt);
    }
}

sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->parent) {
        transform = node->getTransform() * transform;
    }

    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}

Category::Type SceneNode::getCategory() const {
    return Category::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time deltaTime) {
    if (command.categoryFilter & getCategory()) {
        command.action(*this, deltaTime);
    }

    for (const SceneNodePtr &child : children) {
        child->onCommand(command, deltaTime);
    }
}