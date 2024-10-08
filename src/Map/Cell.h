#pragma once

#include "../Effect/Effect.h"
#include "../Object/Item.h"
#include "../Character/Player.h"

class Cell
{
public:
    Cell(char symbol);
    ~Cell();

    void addPlayer(Player* player);
    void removePlayer();

    void setSymbol(char symbol);

    void addEffect(Effect* effect);
    void removeEffect(Effect* effect);
    const std::vector<Effect*>& getEffects() const;

    void setItem(Item* item);
    Item* getItem() const;

    char getSymbol() const;
    
    // Declare is the cell has been seen by the player
    // When a cell has been visited, if it's not in sight, it will be displayed as a dark cell
    bool isExplored;
    bool isInSight;

    bool isWalkable;
private:
    Player* player;

    std::vector<Effect*> effects;
    Item* item;

    char symbol;


};

