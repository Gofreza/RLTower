#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>
#include <functional>

#include "../Characters/CharactersManager.h"
#include "../Localization/LocalizationManager.h"
#include "../Effect/EffectManager.h"
#include "../../Misc/Logger.h"
#include "../../Object/Item.h"
#include "../../Object/Equipment/Weapon.h"
#include "../../Object/Equipment/Shield.h"
#include "../../Object/Equipment/Helmet.h"
#include "../../Object/Equipment/Gloves.h"
#include "../../Object/Equipment/Chests.h"
#include "../../Object/Equipment/Leggings.h"
#include "../../Object/Equipment/Ring.h"
#include "../../Object/Equipment/Amulet.h"
#include "../../Object/Misc/Consumable.h"
#include "../../Object/Misc/Projectile.h"
#include "../../Object/Misc/Containers.h"

class ItemManager
{
public:
    static ItemManager& instance() {
        static ItemManager instance;
        return instance;
    }

    void loadItemsFromFile(const std::string& ItemsFilePath);

    Item* getItem(short id) const;
private:
    bool isInitialize;
    Player* player;

    std::unordered_map<short, Item*> items;

    ItemManager();
    ~ItemManager();

    RarityType getRarity(const std::string rarity) const;
    WeaponType getWeaponType(const std::string& weaponType) const;

    ItemManager(const ItemManager&) = delete;
    ItemManager& operator=(const ItemManager&) = delete;
};
