#include "Cell.h"

Cell::Cell(char baseSymbol, SDL_Color baseColor)
: baseSymbol(baseSymbol), currentSymbol(baseSymbol),
  item(nullptr),
  isWalkable(false),
  isExplored(false),
  isInSight(false),
  baseColor(baseColor), currentColor(baseColor)
{
    int ascii_value = static_cast<int>(baseSymbol);

    // 46 = '.'
    if (ascii_value == 46) {
        isWalkable = true;
    }
}

void Cell::addPlayer(Player* player)
{
    this->player = player;
    this->currentSymbol = player->getSymbol();
}

void Cell::removePlayer()
{
    player = nullptr;
    currentSymbol = baseSymbol;
}

void Cell::setSymbol(char symbol)
{
    this->currentSymbol = symbol;
}

void Cell::resetCell()
{
    currentSymbol = baseSymbol;
    currentColor = baseColor;
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
    return currentSymbol;
}

Cell::~Cell()
{
    if (item)
        delete item;
}
