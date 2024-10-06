#include "Cell.h"

Cell::Cell(char symbol)
: symbol(symbol), item(nullptr),
  isWalkable(false)
{
    int ascii_value = static_cast<int>(symbol);

    // 46 = '.'
    if (ascii_value == 46) {
        isWalkable = true;
    }
}

void Cell::setSymbol(char symbol)
{
    this->symbol = symbol;
}

void Cell::addEffect(Effect* effect)
{
    effects.push_back(effect);
}

void Cell::removeEffect(Effect* effect)
{
    effects.erase(std::remove(effects.begin(), effects.end(), effect), effects.end());
}

const std::vector<Effect*>& Cell::getEffects() const
{
    return effects;
}

void Cell::setItem(Item* item)
{
    this->item = item;
}

Item* Cell::getItem() const
{
    return item;
}

char Cell::getSymbol() const {
    return symbol;
}

Cell::~Cell()
{
    if (item)
        delete item;
}
