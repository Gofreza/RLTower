#pragma once

#include "../Effect/Effect.h"
#include "../Object/Item.h"
#include "../Character/Player.h"

class Cell
{
public:
    Cell(int x, int y, char baseSymbol, SDL_Color baseColor);
    ~Cell();

    bool hasCharacter() const;

    void addCharacter(Character* character);
    void removeCharacter();
    Character* getCharacter() const;

    void setSymbol(char symbol);
    void setLastSeenSymbol(char symbol);
    void resetCell();

    void addEffect(Effect* effect);
    void removeEffect(Effect* effect);
    const std::vector<Effect*>& getEffects() const;
    void updateEffects();

    void setItem(Item* item);
    Item* takeItem();
    Item* getItem() const;
    bool hasItem() const;

    char getSymbol() const;
    char getLastSeenSymbol() const;

    void setX(int x);
    int getX() const;
    void setY(int y);
    int getY() const;

    // Colors
    SDL_Color baseColor;
    SDL_Color currentColor;
    
    // Declare is the cell has been seen by the player
    // When a cell has been visited, if it's not in sight, it will be displayed as a dark cell
    bool isExplored;
    bool isInSight;

    bool isWalkable;
private:
    int x;
    int y;

    Character* character;

    std::vector<Effect*> effects;
    Item* item;

    char baseSymbol;
    char currentSymbol;
    char lastSeenSymbol;

};

