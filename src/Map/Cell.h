#pragma once

#include "../Effect/Effect.h"
#include "../Object/Item.h"

class Cell
{
public:
    Cell(char symbol);
    ~Cell();

    void setSymbol(char symbol);

    void addEffect(Effect* effect);
    void removeEffect(Effect* effect);
    const std::vector<Effect*>& getEffects() const;

    void setItem(Item* item);
    Item* getItem() const;

    char getSymbol() const;
    
    bool isWalkable;
private:
    std::vector<Effect*> effects;
    Item* item;

    char symbol;
};

