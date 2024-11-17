#include "Cell.h"

Cell::Cell(char symbol)
: symbol(symbol), item(nullptr),
  isWalkable(false),
  isExplored(false),
  isInSight(false)
{
    int ascii_value = static_cast<int>(symbol);

    // 46 = '.'
    if (ascii_value == 46) {
        isWalkable = true;
    }
}

void Cell::addPlayer(Player* player)
{
    this->player = player;
    this->symbol = '@';
}

void Cell::removePlayer()
{
    player = nullptr;
    symbol = '.';
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
