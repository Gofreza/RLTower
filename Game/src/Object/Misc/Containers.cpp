#include "Containers.h"
#include "../../Character/Character.h"

Containers::Containers(short id, std::string name, std::string description, ItemType type, float weight, RarityType rarity,
    std::string imagePath,
    std::list<short> itemsIds, float weightReduce)
: Misc(id, name, description, type, weight, rarity, imagePath),
acceptedItems(itemsIds), weightReduce(weightReduce / 100)
{}

Containers::Containers(const Containers& containers) 
: Misc(containers.getId(), containers.getName(), containers.getDescription(), containers.getType(), containers.getWeight(), containers.getRarity(), containers.getImagePath(), containers.getEffects()),
items(containers.items), acceptedItems(containers.acceptedItems), weightReduce(containers.weightReduce)
{}

Containers* Containers::clone() const {
    return new Containers(*this);
}

void Containers::use(Character* character) {
    std::vector<Item*>& inventory = character->getInventory();

    // Remove accepted items if they exists and add them to the container
    for (auto it = inventory.begin(); it != inventory.end(); ) {
        Item* item = *it;
        short itemId = item->getId();

        // Check if the item's ID is in the acceptedItems list
        if (std::find(acceptedItems.begin(), acceptedItems.end(), itemId) != acceptedItems.end()) {
            // The item is accepted, add it to the container's items list
            items.push_back(item);
            
            // Update weigth and remove the item from the inventory
            // Deduce weight of items
            character->setWeight(character->getWeight() - item->getWeight());
            // Update weight of container and put it back
            float newWeight = this->getWeight() + (item->getWeight() * weightReduce);
            character->setWeight(character->getWeight() - this->getWeight());
            this->setWeight(newWeight);
            character->setWeight(character->getWeight() + newWeight);
            it = inventory.erase(it); 
        } else {
            ++it; 
        }
    }
}

// Get the list of all items in the container
const std::list<Item*>& Containers::getItems() const {
    return items;
}

size_t Containers::getItemsNumberInContainer() const {
    return items.size();
}

float Containers::getWeightReduce() const {
    return weightReduce;
}

Containers::~Containers()
{
    for (auto& item : items) {
        if (item) {
            delete item;
        }
    }
    items.clear();
    acceptedItems.clear();
}