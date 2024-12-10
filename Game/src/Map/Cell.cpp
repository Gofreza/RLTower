#include "Cell.h"

Cell::Cell(int x, int y, char baseSymbol, SDL_Color baseColor): 
    baseColor(baseColor), currentColor(baseColor), 
    isExplored(false), isInSight(false), isWalkable(false),
    x(x), y(y),
    character(nullptr),
    item(nullptr),
    baseSymbol(baseSymbol), currentSymbol(baseSymbol)
{
    int ascii_value = static_cast<int>(baseSymbol);

    // 46 = '.'
    if (ascii_value == 46) {
        isWalkable = true;
    }
}

bool Cell::hasCharacter() const {
    return character != nullptr;
}

void Cell::addCharacter(Character* character)
{
    this->character = character;
    this->currentSymbol = character->getSymbol();
}

void Cell::removeCharacter()
{
    character = nullptr;
    currentSymbol = baseSymbol;
}

Character* Cell::getCharacter() const
{
    return character;
}

void Cell::setSymbol(char symbol)
{
    this->currentSymbol = symbol;
}

void Cell::resetCell()
{
    if (!item) {
        currentSymbol = baseSymbol;
        currentColor = baseColor;
    } else {
        currentSymbol = to_char(item->getType());
        currentColor = to_color(item->getType());
    }
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

void Cell::setItem(Item* item) {
    this->item = item;
    this->currentSymbol = to_char(item->getType());
    this->currentColor = to_color(item->getType());
}

Item* Cell::takeItem() {
    this->resetCell();
    auto item = this->item;
    this->item = nullptr;
    resetCell();
    return item;
}

Item* Cell::getItem() const {
    return item;
}

bool Cell::hasItem() const {
    return item != nullptr;
}

char Cell::getSymbol() const {
    return currentSymbol;
}

void Cell::setX(int x)
{
    this->x = x;
}

int Cell::getX() const
{
    return x;
}

void Cell::setY(int y)
{
    this->y = y;
}

int Cell::getY() const
{
    return y;
}

Cell::~Cell()
{
    if (item)
        delete item;
}
