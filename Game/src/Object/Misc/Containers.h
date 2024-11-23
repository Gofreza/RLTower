#pragma once

#include <list>
#include "Misc.h"

class Containers : public Misc
{
public:
    Containers(short id, std::string name, std::string description, ItemType type, int weight, RarityType rarity,
            std::list<short> itemsIds,
            float weightReduce);
    ~Containers();
    Containers(const Containers& containers);

    virtual Containers* clone() const override;

    void use(Character* character);
    const std::list<Item*>& getItems() const;
    size_t getItemsNumberInContainer() const;
    float getWeightReduce() const;
private:
    std::list<Item*> items;
    // Id of acceptable objects
    std::list<short> acceptedItems;

    float weightReduce;
};