#include "scene/CreatureCatalog.hpp"

CreatureCatalog::CreatureCatalog()
: creatures(2) {

}

void CreatureCatalog::addCreature(CreatureData& creatureData) {
    assert(static_cast<unsigned int>(creatureData.type) < creatures.size());
    creatures[static_cast<unsigned int>(creatureData.type)] = creatureData;
}

CreatureDataSptr CreatureCatalog::getCreature(CreatureType creatureType) {
    assert(static_cast<unsigned int>(creatureType) < creatures.size());
    std::shared_ptr<CreatureData> creaturePtr(&creatures[static_cast<unsigned int>(creatureType)]);
    return creaturePtr;
}

CreatureCatalogUptr initializeCreatureData() {
    CreatureData humanData;
    humanData.type = CreatureType::Human;
    humanData.hitPoints = 7;
    humanData.textureId = TextureId::Human;
    humanData.speed = 90.f;

    //North - Walking
    humanData.walkingFrames.push_back({Heading::North, sf::IntRect(64, 512, 64, 64)});
    humanData.walkingFrames.push_back({Heading::North, sf::IntRect(128, 512, 64, 64)});
    humanData.walkingFrames.push_back({Heading::North, sf::IntRect(192, 512, 64, 64)});
    humanData.walkingFrames.push_back({Heading::North, sf::IntRect(256, 512, 64, 64)});
    humanData.walkingFrames.push_back({Heading::North, sf::IntRect(320, 512, 64, 64)});
    humanData.walkingFrames.push_back({Heading::North, sf::IntRect(384, 512, 64, 64)});
    humanData.walkingFrames.push_back({Heading::North, sf::IntRect(448, 512, 64, 64)});
    humanData.walkingFrames.push_back({Heading::North, sf::IntRect(512, 512, 64, 64)});

    //West - Walking
    humanData.walkingFrames.push_back({Heading::West, sf::IntRect(64, 576, 64, 64)});
    humanData.walkingFrames.push_back({Heading::West, sf::IntRect(128, 576, 64, 64)});
    humanData.walkingFrames.push_back({Heading::West, sf::IntRect(192, 576, 64, 64)});
    humanData.walkingFrames.push_back({Heading::West, sf::IntRect(256, 576, 64, 64)});
    humanData.walkingFrames.push_back({Heading::West, sf::IntRect(320, 576, 64, 64)});
    humanData.walkingFrames.push_back({Heading::West, sf::IntRect(384, 576, 64, 64)});
    humanData.walkingFrames.push_back({Heading::West, sf::IntRect(448, 576, 64, 64)});
    humanData.walkingFrames.push_back({Heading::West, sf::IntRect(512, 576, 64, 64)});

    //South - Walking
    humanData.walkingFrames.push_back({Heading::South, sf::IntRect(64, 640, 64, 64)});
    humanData.walkingFrames.push_back({Heading::South, sf::IntRect(128, 640, 64, 64)});
    humanData.walkingFrames.push_back({Heading::South, sf::IntRect(192, 640, 64, 64)});
    humanData.walkingFrames.push_back({Heading::South, sf::IntRect(256, 640, 64, 64)});
    humanData.walkingFrames.push_back({Heading::South, sf::IntRect(320, 640, 64, 64)});
    humanData.walkingFrames.push_back({Heading::South, sf::IntRect(384, 640, 64, 64)});
    humanData.walkingFrames.push_back({Heading::South, sf::IntRect(448, 640, 64, 64)});
    humanData.walkingFrames.push_back({Heading::South, sf::IntRect(512, 640, 64, 64)});

    //East - Walking
    humanData.walkingFrames.push_back({Heading::East, sf::IntRect(64, 704, 64, 64)});
    humanData.walkingFrames.push_back({Heading::East, sf::IntRect(128, 704, 64, 64)});
    humanData.walkingFrames.push_back({Heading::East, sf::IntRect(192, 704, 64, 64)});
    humanData.walkingFrames.push_back({Heading::East, sf::IntRect(256, 704, 64, 64)});
    humanData.walkingFrames.push_back({Heading::East, sf::IntRect(320, 704, 64, 64)});
    humanData.walkingFrames.push_back({Heading::East, sf::IntRect(384, 704, 64, 64)});
    humanData.walkingFrames.push_back({Heading::East, sf::IntRect(448, 704, 64, 64)});
    humanData.walkingFrames.push_back({Heading::East, sf::IntRect(512, 704, 64, 64)});

    //North - Standing
    humanData.standingFrames.push_back({Heading::North, sf::IntRect(0, 512, 64, 64)});

    //West - Standing
    humanData.standingFrames.push_back({Heading::West, sf::IntRect(0, 576, 64, 64)});

    //South - Standing
    humanData.standingFrames.push_back({Heading::South, sf::IntRect(0, 640, 64, 64)});

    //East - Standing
    humanData.standingFrames.push_back({Heading::East, sf::IntRect(0, 704, 64, 64)});

    //Orc - same frame breakdown as humans with different stats
    CreatureData orcData = humanData;
    orcData.type = CreatureType::Orc;
    orcData.hitPoints = 10;
    orcData.textureId = TextureId::Orc;
    orcData.speed = 95.f;

    CreatureCatalogUptr creatureCatalog(new CreatureCatalog{});

    creatureCatalog->addCreature(humanData);
    creatureCatalog->addCreature(orcData);

    return creatureCatalog;
}