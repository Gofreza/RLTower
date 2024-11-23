#pragma once

#include <iostream>
#include <vector>
#include "../../Character/Character.h"
#include "../../Character/Player.h"
#include "../../Character/NPC.h"

// Manager for Player Character and NPC Characters
class CharactersManager
{
public:
    static CharactersManager& instance() {
        static CharactersManager instance;
        return instance;
    }
    
    void setPlayer(Player* player);
    Player* getPlayer() const;

    void addNPC(NPC* npc);

private:
    Player* player;
    std::vector<NPC*> npcs;

    CharactersManager();
    ~CharactersManager();

    // Prevent copying
    CharactersManager(const CharactersManager&) = delete;
    CharactersManager& operator=(const CharactersManager&) = delete;

};

