#include "config.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Version " << perseverance_VERSION_MAJOR << "." << perseverance_VERSION_MINOR << endl;

    sf::Window App(sf::VideoMode(800, 600), "myproject");

    tmx::MapLoader ml("path/to/maps");
    ml.Load("map.tmx");

    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();
        }
        App.display();
    }
}
