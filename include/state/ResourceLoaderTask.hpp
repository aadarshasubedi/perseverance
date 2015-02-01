#ifndef RESOURCELOADERTASK_HPP
#define RESOURCELOADERTASK_HPP

#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <functional>

class ResourceLoaderTask {

public:
    explicit ResourceLoaderTask();

public:
    void execute();
    bool isComplete();
    float getCompletion();

private:
    void runTask();

private:
    sf::Thread thread;
    bool finished;
    sf::Clock elapsedTime;
    sf::Mutex mutex;
};

#endif //RESOURCELOADERTASK