#ifndef CREATURECATALOG_HPP
#define CREATURECATALOG_HPP

#include "util/Resources.hpp"

#include <vector>
#include <SFML/Graphics/Rect.hpp>

enum class CreatureType : unsigned int{
    Human = 0x00,
    Orc = 0x01
};

enum class Heading : unsigned int {
    North = 0x01,
    West = 0x02,
    South = 0x03,
    East = 0x04
};

struct AnimationFrame {
    Heading heading;
    sf::IntRect frame;
};

struct CreatureData {
    CreatureType type;
    int hitPoints;
    float speed;
    TextureId textureId;
    std::vector<AnimationFrame> walkingFrames;
    std::vector<AnimationFrame> standingFrames;
};

using CreatureDataSptr = std::shared_ptr<CreatureData>;

class CreatureCatalog {
public:
    explicit CreatureCatalog();

public:
    void addCreature(CreatureData& creatureData);
    CreatureDataSptr getCreature(CreatureType creatureType);

private:
    std::vector<CreatureData> creatures;
};

using CreatureCatalogUptr = std::unique_ptr<CreatureCatalog>;

CreatureCatalogUptr initializeCreatureData();

#endif //CREATURECATALOG_HPP