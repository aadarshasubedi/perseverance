#include <iostream>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "Application.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Version " << perseverance_VERSION_MAJOR << "." << perseverance_VERSION_MINOR << endl;
    sf::Vector2i screenDimensions(800, 600);
    try {
        Application application(screenDimensions);
        application.run();
    } catch(std::exception& e) {
        std::cout << "Error encountered: " << e.what() << std::endl;
    }

}