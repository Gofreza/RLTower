#include "CharactersManager.h"

CharactersManager::CharactersManager() {
}

CharactersManager::~CharactersManager() {
    if (player) {
        delete player;
    }
    for (auto& NPC : npcs) {
        delete NPC;
    }
    npcs.clear();
}

void CharactersManager::setPlayer(Player* player) {
    this->player = player;
}

Player* CharactersManager::getPlayer() const {
    return this->player;
}

void CharactersManager::addNPC(NPC* npc) {
    this->npcs.push_back(npc);
} 