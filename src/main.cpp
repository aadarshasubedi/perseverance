#include "config.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Version " << perseverance_VERSION_MAJOR << "." << perseverance_VERSION_MINOR << endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "myproject");

    tmx::MapLoader ml("resources/maps");
    ml.AddSearchPath("resources/maps/atlas");
    ml.Load("landing.tmx");

    sf::Texture texture;
    if (!texture.loadFromFile("resources/sprites/body/male/tanned.png")) {
        return -1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen()) {
        sf::Event Event;
        while (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
//        window.draw(sprite);
        window.draw(ml);
    }
}
