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

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> sceneNodeAction(Function subClassFunction) {
    return [=] (SceneNode& node, sf::Time deltaTime) {
        assert(nullptr != dynamic_cast<GameObject*>(&node));
        subClassFunction(static_cast<GameObject&>(node), deltaTime);
    };
}

#endif //COMMAND_HPP