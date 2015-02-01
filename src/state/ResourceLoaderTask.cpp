#include <SFML/System/Clock.hpp>
#include <SFML/System/Lock.hpp>
#include "state/ResourceLoaderTask.hpp"

ResourceLoaderTask::ResourceLoaderTask()
        : thread(&ResourceLoaderTask::runTask, this),
          finished(false),
          elapsedTime(),
          mutex() {
}

void ResourceLoaderTask::execute() {
    finished = false;
    elapsedTime.restart();
    thread.launch();
}

bool ResourceLoaderTask::isComplete() {
    sf::Lock lock(mutex);
    return finished;
}

float ResourceLoaderTask::getCompletion() {
    sf::Lock lock(mutex);

    return elapsedTime.getElapsedTime().asSeconds() / 10.f; //Hard coded for demonstratoin
}

void ResourceLoaderTask::runTask() {
    bool endRun = false;

    while (!endRun) {
        sf::Lock lock(mutex);
        if (elapsedTime.getElapsedTime().asSeconds() >= 10.f) {
            endRun = true;
        }
    }

    //Locks are set up using RAII pattern.
    {
        sf::Lock lock(mutex);
        finished = true;
    }
}