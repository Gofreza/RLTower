#include "ItemManager.h"

ItemManager::ItemManager()
: isInitialize(false), player(CharactersManager::instance().getPlayer())
{
}

void ItemManager::loadItemsFromFile(const std::string& ItemsFilePath) {
    std::ifstream file(ItemsFilePath);
    if (!file.is_open()) {
        isInitialize = false;
        std::cout << "Error loading items" << std::endl;
    } else {
        nlohmann::json jsonData;
        try {
            file >> jsonData;
            //std::cout << jsonData.dump(4) << std::endl;  // Pretty prints the JSON with 4 spaces of indentation
        } catch (nlohmann::json::parse_error& e) {
            std::cout << "Error parsing JSON: " << e.what() << std::endl;
            isInitialize = false;
            return;
        }

        if (!jsonData.contains("items") || !jsonData["items"].is_array()) {
            std::cout << "Invalid JSON format: 'items' key missing or not an array." << std::endl;
            isInitialize = false;
            return;
        }

        for (const auto& itemJson : jsonData["items"]) {
            std::string typeStr = itemJson.value("type", "Miscellaneous");
            Item* item;
            ItemType type;
            // std::cout << "Name: " << itemJson.value("name", "Unknown") << std::endl;
            if (typeStr == "Weapon") {
                type = ItemType::Weapon;
                std::string wTypeString = itemJson.value("wType", "None");
                item = new Weapon(itemJson.value("id", -1), 
                                itemJson.value("name", "Unknown"), 
                                itemJson.value("description", "Unknown"), 
                                type,
                                getWeaponType(wTypeString),
                                itemJson.value("weight", -1),
                                itemJson.value("durability", -1),
                                getRarity(itemJson.value("rarity", "Poor")),
                                itemJson.value("phyDamage", -1),
                                itemJson.value("magDamage", -1),
                                getDamageType(itemJson.value("damageType", "None")),
                                itemJson.value("twoHanded", false),
                                itemJson.value("length", 1),
                                itemJson.value("magical", false),
                                itemJson.value("phyDefense", 0),
                                itemJson.value("magDefense", 0),
                                EffectManager::instance().getEffect(itemJson.value("effect", std::list<std::string>{"None"})),
                                itemJson.value("requirements", std::array<int, 5>{-1, -1, -1, -1}));
            } else if (typeStr == "Shield") {
                type = ItemType::Shield;
                item = new Shield(itemJson.value("id", -1),
                                itemJson.value("name", "Unknown"), 
                                itemJson.value("description", "Unknown"), 
                                type,
                                itemJson.value("weight", -1),
                                itemJson.value("durability", -1),
                                getRarity(itemJson.value("rarity", "Poor")),
                                itemJson.value("phyDefense", 0),
                                itemJson.value("magDefense", 0),
                                itemJson.value("parryChance", 0),
                                EffectManager::instance().getEffect(itemJson.value("effect", std::list<std::string>{"None"})),
                                itemJson.value("requirements", std::array<int, 5>{-1, -1, -1, -1}));
            } else if (typeStr == "Helmet") {
                type = ItemType::Helmet;
                item = new Helmet(itemJson.value("id", -1),
                                itemJson.value("name", "Unknown"), 
                                itemJson.value("description", "Unknown"), 
                                type,
                                itemJson.value("weight", -1),
                                itemJson.value("durability", -1),
                                getRarity(itemJson.value("rarity", "Poor")),
                                itemJson.value("phyDefense", 0),
                                itemJson.value("magDefense", 0),
                                EffectManager::instance().getEffect(itemJson.value("effect", std::list<std::string>{"None"})),
                                itemJson.value("requirements", std::array<int, 5>{-1, -1, -1, -1}));
            } else if (typeStr == "Gloves") {
                type = ItemType::Gloves;
                item = new Gloves(itemJson.value("id", -1),
                                itemJson.value("name", "Unknown"), 
                                itemJson.value("description", "Unknown"), 
                                type,
                                itemJson.value("weight", -1),
                                itemJson.value("durability", -1),
                                getRarity(itemJson.value("rarity", "Poor")),
                                itemJson.value("phyDefense", 0),
                                itemJson.value("magDefense", 0),
                                EffectManager::instance().getEffect(itemJson.value("effect", std::list<std::string>{"None"})),
                                itemJson.value("requirements", std::array<int, 5>{-1, -1, -1, -1}));
            } else if (typeStr == "ChestArmor") {
                type = ItemType::ChestArmor;
                item = new Chests(itemJson.value("id", -1),
                                itemJson.value("name", "Unknown"), 
                                itemJson.value("description", "Unknown"), 
                                type,
                                itemJson.value("weight", -1),
                                itemJson.value("durability", -1),
                                getRarity(itemJson.value("rarity", "Poor")),
                                itemJson.value("phyDefense", 0),
                                itemJson.value("magDefense", 0),
                                EffectManager::instance().getEffect(itemJson.value("effect", std::list<std::string>{"None"})),
                                itemJson.value("requirements", std::array<int, 5>{-1, -1, -1, -1}));
            } else if (typeStr == "LegArmor") {
                type = ItemType::LegArmor;
                item = new Leggings(itemJson.value("id", -1),
                                itemJson.value("name", "Unknown"), 
                                itemJson.value("description", "Unknown"), 
                                type,
                                itemJson.value("weight", -1),
                                itemJson.value("durability", -1),
                                getRarity(itemJson.value("rarity", "Poor")),
                                itemJson.value("phyDefense", 0),
                                itemJson.value("magDefense", 0),
                                EffectManager::instance().getEffect(itemJson.value("effect", std::list<std::string>{"None"})),
                                itemJson.value("requirements", std::array<int, 5>{-1, -1, -1, -1}));
            } else if (typeStr == "Ring") {
                type = ItemType::Ring;
                item = new Ring(itemJson.value("id", -1),
                                itemJson.value("name", "Unknown"), 
                                itemJson.value("description", "Unknown"), 
                                type,
                                itemJson.value("weight", -1),
                                itemJson.value("durability", -1),
                                getRarity(itemJson.value("rarity", "Poor")),
                                itemJson.value("phyDefense", 0),
                                itemJson.value("magDefense", 0),
                                EffectManager::instance().getEffect(itemJson.value("effect", std::list<std::string>{"None"})),
                                itemJson.value("requirements", std::array<int, 5>{-1, -1, -1, -1}));
            } else if (typeStr == "Amulet") {
                type = ItemType::Amulet;
                item = new Amulet(itemJson.value("id", -1),
                                itemJson.value("name", "Unknown"), 
                                itemJson.value("description", "Unknown"), 
                                type,
                                itemJson.value("weight", -1),
                                itemJson.value("durability", -1),
                                getRarity(itemJson.value("rarity", "Poor")),
                                itemJson.value("phyDefense", 0),
                                itemJson.value("magDefense", 0),
                                EffectManager::instance().getEffect(itemJson.value("effect", std::list<std::string>{"None"})),
                                itemJson.value("requirements", std::array<int, 5>{-1, -1, -1, -1}));
            } else if (typeStr == "Consumable") {
                type = ItemType::Consumable;
                item = new Consumable(itemJson.value("id", -1),
                                itemJson.value("name", "Unknown"), 
                                itemJson.value("description", "Unknown"), 
                                type,
                                itemJson.value("weight", -1),
                                getRarity(itemJson.value("rarity", "Poor")),
                                EffectManager::instance().getEffect(itemJson.value("effect", std::list<std::string>{"None"})));
            } else if (typeStr == "Projectile") {
                type = ItemType::Projectile;
                item = new Projectile(itemJson.value("id", -1),
                                itemJson.value("name", "Unknown"), 
                                itemJson.value("description", "Unknown"), 
                                type,
                                itemJson.value("weight", -1),
                                getRarity(itemJson.value("rarity", "Poor")),
                                itemJson.value("damage", -1),
                                getDamageType(itemJson.value("damageType", "None")));
            } else if (typeStr == "Container") {
                type = ItemType::Container;
                item = new Containers(itemJson.value("id", -1),
                                    itemJson.value("name", "Unknow"),
                                    itemJson.value("description", "Unknown"),
                                    type,
                                    itemJson.value("weight", -1),
                                    getRarity(itemJson.value("rarity", "Poor")),
                                    itemJson.value("itemIds", std::list<short>{}),
                                    itemJson.value("weightReduce", 100));
            } else if (typeStr == "QuestItem") {
                type = ItemType::QuestItem;
            } else {
                type = ItemType::Miscellaneous;
            }

            items.emplace(item->getId(), item);            
        }

        isInitialize = true;
        std::cout << "Items loaded" << std::endl;
    }
}

/**
 * @brief Get an item by ID
 * @return A copy of the item
 */
Item* ItemManager::getItem(short id) const {
    if (!isInitialize) {
        throw std::runtime_error("ItemManager is not initialized. (getItem)");
    }

    auto it = items.find(id);
    if (it != items.end()) {
        return it->second->clone();
    }

    throw std::runtime_error("Item with ID " + std::to_string(id) + " not found.");
}

RarityType ItemManager::getRarity(const std::string rarity) const {
    if (rarity == "Poor") {
        return RarityType::Poor;
    } else if (rarity == "Normal") {
        return RarityType::Normal;
    } else if (rarity == "Good") {
        return RarityType::Good;
    } else if (rarity == "Rare") {
        return RarityType::Rare;
    } else if (rarity == "Epic") {
        return RarityType::Epic;
    } else if (rarity == "Legendary") {
        return RarityType::Legendary;
    } else if (rarity == "Mythical") {
        return RarityType::Mythical;
    } else {
        return RarityType::Poor;
    }
}

WeaponType ItemManager::getWeaponType(const std::string& weaponType) const {
    if (weaponType == "Sword") {
        return WeaponType::Sword;
    } else if (weaponType == "Spear") {
        return WeaponType::Spear;
    } else if (weaponType == "Mace") {
        return WeaponType::Mace;
    } else if (weaponType == "Bow") {
        return WeaponType::Bow;
    } else if (weaponType == "Staff") {
        return WeaponType::Staff;
    } else {
        return WeaponType::None;
    }
}

ItemManager::~ItemManager() {
    for (auto& pair : items) {
        if (pair.second)
            delete pair.second;
    }
}