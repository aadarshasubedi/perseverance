#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include "Category.hpp"

class Command;

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {

public:
    typedef std::unique_ptr<SceneNode> SceneNodePtr;

public:
    SceneNode();

public:
    void attachChild(SceneNodePtr sceneNode);
    SceneNodePtr detachChild(const SceneNode &sceneNode);
    void update(sf::Time dt);
    sf::Vector2f getWorldPosition() const;
    void onCommand(const Command& command, sf::Time deltaTime);

public:
    virtual Category::Type getCategory() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    virtual sf::Transform getWorldTransform() const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);

private:
    std::vector<SceneNodePtr> children;
    //SceneNodes are owned uniquely by the SceneGraph in which they are contained.
    SceneNode* parent;
};

#endif // SCENENODE_HPP