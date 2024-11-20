#pragma once

#include "../Effect/Effect.h"
#include "../Object/Item.h"
#include "../Character/Player.h"

class Cell
{
public:
    Cell(char baseSymbol, SDL_Color baseColor);
    ~Cell();

    bool hasCharacter() const;

    void addCharacter(Character* character);
    void removeCharacter();

    void setSymbol(char symbol);
    void resetCell();

    void addEffect(Effect* effect);
    void removeEffect(Effect* effect);
    const std::vector<Effect*>& getEffects() const;

    void setItem(Item* item);
    Item* getItem() const;

    char getSymbol() const;

    // Colors
    SDL_Color baseColor;
    SDL_Color currentColor;
    
    // Declare is the cell has been seen by the player
    // When a cell has been visited, if it's not in sight, it will be displayed as a dark cell
    bool isExplored;
    bool isInSight;

    bool isWalkable;
private:
    Character* character;

    std::vector<Effect*> effects;
    Item* item;

    char baseSymbol;
    char currentSymbol;

};

