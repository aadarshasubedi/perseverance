#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/System/Time.hpp>
#include <functional>
#include <cassert>

class SceneNode;

struct Command {
    Command();
    std::function<void(SceneNode&, sf::Time)> action;
    unsigned int categoryFilter;
};

template <typename SceneNodeSubclass, typename Function>
std::function<void(SceneNode&, sf::Time)> sceneNodeAction(Function subClassFunction) {
    return [=] (SceneNode& node, sf::Time deltaTime) {
        assert(nullptr != dynamic_cast<SceneNodeSubclass*>(&node));
        subClassFunction(static_cast<SceneNodeSubclass&>(node), deltaTime);
    };
}

#endif //COMMAND_HPP