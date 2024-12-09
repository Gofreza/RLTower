#include "EquipmentMenu.h"

#include "../Manager/Localization/LocalizationManager.h"
#include "../Manager/UI/UiManager.h"

int borderThickness = 2;

EquipmentMenu::EquipmentMenu(SDL_Renderer* renderer, TTF_Font* font) 
    : Menu(renderer, font)
{
    //=====================================================================
    // Layout:
    // Border - Padding - Text - Padding - Text - Padding - Border
    //=====================================================================
    padding = 15;
    player = CharactersManager::instance().getPlayer();

    std::string headerText =  LocalizationManager::instance().getText("equipments_title");
    headerTextTexture = Utils::loadTextTexture(renderer, font, headerText, Utils::textColor);

    // When construct, pre-render every elements    
    menuHeight = (borderThickness * 2) + padding;
    maxTextTextureWidth = 0;

    // Pre-Render Menu
    int textWidth = 0, textHeight = 0;
    std::string lhText =  LocalizationManager::instance().getText("left_hand_equipment");
    lhTextTexture = Utils::loadTextTexture(renderer, font, lhText, Utils::textColor);
    if (lhTextTexture) {
        SDL_QueryTexture(lhTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        menuHeight += textHeight + padding;
    }
    if (textWidth > maxTextTextureWidth) {
        maxTextTextureWidth = textWidth;
    }

    std::string rhText = LocalizationManager::instance().getText("right_hand_equipment");
    rhTextTexture = Utils::loadTextTexture(renderer, font, rhText, Utils::textColor);
    if (rhTextTexture) {
        SDL_QueryTexture(rhTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        menuHeight += textHeight + padding;
    }
    if (textWidth > maxTextTextureWidth) {
        maxTextTextureWidth = textWidth;
    }

    std::string headText = LocalizationManager::instance().getText("head_equipment");
    headTextTexture = Utils::loadTextTexture(renderer, font, headText, Utils::textColor);
    if (headTextTexture) {
        SDL_QueryTexture(headTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        menuHeight += textHeight + padding;
    }
    if (textWidth > maxTextTextureWidth) {
        maxTextTextureWidth = textWidth;
    }

    std::string torsoText = LocalizationManager::instance().getText("torso_equipment");
    torsoTextTexture = Utils::loadTextTexture(renderer, font, torsoText, Utils::textColor);
    if (torsoTextTexture) {
        SDL_QueryTexture(torsoTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        menuHeight += textHeight + padding;
    }
    if (textWidth > maxTextTextureWidth) {
        maxTextTextureWidth = textWidth;
    }

    std::string handText = LocalizationManager::instance().getText("hands_equipment");
    handTextTexture = Utils::loadTextTexture(renderer, font, handText, Utils::textColor);
    if (handTextTexture) {
        SDL_QueryTexture(handTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        menuHeight += textHeight + padding;
    }
    if (textWidth > maxTextTextureWidth) {
        maxTextTextureWidth = textWidth;
    }

    std::string footText = LocalizationManager::instance().getText("foot_equipment");
    footTextTexture = Utils::loadTextTexture(renderer, font, footText, Utils::textColor);
    if (footTextTexture) {
        SDL_QueryTexture(footTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        menuHeight += textHeight + padding;
    }
    if (textWidth > maxTextTextureWidth) {
        maxTextTextureWidth = textWidth;
    }

    std::string ringText = LocalizationManager::instance().getText("ring_equipment");
    ringTextTexture = Utils::loadTextTexture(renderer, font, ringText, Utils::textColor);
    if (ringTextTexture) {
        SDL_QueryTexture(ringTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        menuHeight += textHeight + padding;
    }
    if (textWidth > maxTextTextureWidth) {
        maxTextTextureWidth = textWidth;
    }

    std::string ring2Text = LocalizationManager::instance().getText("ring_equipment");
    ring2TextTexture = Utils::loadTextTexture(renderer, font, ring2Text, Utils::textColor);
    if (ring2TextTexture) {
        SDL_QueryTexture(ring2TextTexture, nullptr, nullptr, &textWidth, &textHeight);
        menuHeight += textHeight + padding;
    }
    if (textWidth > maxTextTextureWidth) {
        maxTextTextureWidth = textWidth;
    }

    std::string amuletText = LocalizationManager::instance().getText("amulet_equipment");
    amuletTextTexture = Utils::loadTextTexture(renderer, font, amuletText, Utils::textColor);
    if (amuletTextTexture) {
        SDL_QueryTexture(amuletTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        menuHeight += textHeight + padding;
    }
    if (textWidth > maxTextTextureWidth) {
        maxTextTextureWidth = textWidth;
    }

    initializeTextureToSlotMap();
}

void EquipmentMenu::render(const SDL_Rect& rect) {

    //=====================================================================
    // We do not use rect.x to get where we should draw
    // Because we render into a render target and not directly on the window
    // it's like a new window so top left is (0, 0) and not rect.x
    // So rect.x = 0
    // We still use the width and height though
    //=====================================================================
    
    //=====================================================================
    // Layout:
    // Border - Padding - Text - Padding - Text - Padding - Border
    //=====================================================================

    // Draw the header text
    int textWidth = 0, textHeight = 0;
    if (headerTextTexture) {
        SDL_QueryTexture(headerTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect headerRect = {
            (rect.w - textWidth) / 2, // Center the header text horizontally
            rect.y - textHeight, 
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer, headerTextTexture, nullptr, &headerRect);
    }

    SDL_Rect equipmentRect = {
        0,
        rect.y + textHeight - 5,
        rect.w,
        rect.h - textHeight
    };

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderFillRect(renderer, &equipmentRect);

    // Draw the border
    drawBorder(renderer, equipmentRect, Utils::borderColor, borderThickness);

    // Draw Menu
    int currentY = rect.y + borderThickness + padding;

    renderTextTexture(lhTextTexture, currentY, padding, rect.x, rect.y, rect.w);

    renderTextTexture(rhTextTexture, currentY, padding, rect.x, rect.y, rect.w);

    renderTextTexture(headTextTexture, currentY, padding, rect.x, rect.y, rect.w);

    renderTextTexture(torsoTextTexture, currentY, padding, rect.x, rect.y, rect.w);

    renderTextTexture(handTextTexture, currentY, padding, rect.x, rect.y, rect.w);

    renderTextTexture(footTextTexture, currentY, padding, rect.x, rect.y, rect.w);

    renderTextTexture(ringTextTexture, currentY, padding, rect.x, rect.y, rect.w);

    renderTextTexture(ring2TextTexture, currentY, padding, rect.x, rect.y, rect.w);

    renderTextTexture(amuletTextTexture, currentY, padding, rect.x, rect.y, rect.w);
}  

int EquipmentMenu::getHeight() const {
    return menuHeight;
}

void EquipmentMenu::renderTextTexture(SDL_Texture* textTexture, int& currentY, int padding, int renderTargetX, int renderTargetY, int renderTargetW) {
    if (textTexture) {
        int textWidth = 0, textHeight = 0;
        SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect rect = {
            0 + 10, 
            currentY, 
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer, textTexture, nullptr, &rect);

        auto it = textureToSlotMap.find(textTexture);
        if (it != textureToSlotMap.end()) {
            Item* item = it->second(player);  
            if (item) {
                std::string itemName = item->getName();
                SDL_Texture* itemNameTextTexture = Utils::loadTextTexture(renderer, font, itemName, Utils::textColor);

                std::string durabilityText;
                bool hasDurability = false;
                if (item->getType() == ItemType::Weapon) {
                    Weapon* weapon = static_cast<Weapon*>(item);
                    durabilityText = std::to_string(weapon->getDurability()) + "/" + std::to_string(weapon->getMaxDurability());
                    hasDurability = true;
                } else if (item->getType() == ItemType::Shield) {
                    Shield* shield = static_cast<Shield*>(item);
                    durabilityText = std::to_string(shield->getDurability()) + "/" + std::to_string(shield->getMaxDurability());
                    hasDurability = true;
                } else if (item->getType() == ItemType::Helmet) {
                    Helmet* helmet = static_cast<Helmet*>(item);
                    durabilityText = std::to_string(helmet->getDurability()) + "/" + std::to_string(helmet->getMaxDurability());
                    hasDurability = true;
                } else if (item->getType() == ItemType::Gloves) {
                    Gloves* glove = static_cast<Gloves*>(item);
                    durabilityText = std::to_string(glove->getDurability()) + "/" + std::to_string(glove->getMaxDurability());
                    hasDurability = true;
                } else if (item->getType() == ItemType::ChestArmor) {
                    Chests* chest = static_cast<Chests*>(item);
                    durabilityText = std::to_string(chest->getDurability()) + "/" + std::to_string(chest->getMaxDurability());
                    hasDurability = true;
                } else if (item->getType() == ItemType::LegArmor) {
                    Leggings* legging = static_cast<Leggings*>(item);
                    durabilityText = std::to_string(legging->getDurability()) + "/" + std::to_string(legging->getMaxDurability());
                    hasDurability = true;
                } else if (item->getType() == ItemType::Ring) {
                    Ring* ring = static_cast<Ring*>(item);
                    durabilityText = std::to_string(ring->getDurability()) + "/" + std::to_string(ring->getMaxDurability());
                    hasDurability = true;
                } else if (item->getType() == ItemType::Amulet) {
                    Amulet* amulet = static_cast<Amulet*>(item);
                    durabilityText = std::to_string(amulet->getDurability()) + "/" + std::to_string(amulet->getMaxDurability());
                    hasDurability = true;
                } 

                SDL_Texture* durabilityTexture = nullptr;
                if (hasDurability) {
                    durabilityTexture = Utils::loadTextTexture(renderer, font, durabilityText, Utils::textColor);
                }

                if (itemNameTextTexture)
                {
                    SDL_QueryTexture(itemNameTextTexture, nullptr, nullptr, &textWidth, &textHeight);
                
                    SDL_Rect equipmentSlotRect = {
                        10 + maxTextTextureWidth + 10,
                        currentY,
                        textWidth,
                        textHeight
                    };

                    SDL_Rect durabilityRect = {};
                    int durabilityWidth = 0, durabilityHeight = 0;
                    if (hasDurability && durabilityTexture) {
                        SDL_QueryTexture(durabilityTexture, nullptr, nullptr, &durabilityWidth, &durabilityHeight);

                        durabilityRect = {
                            0 + renderTargetW - durabilityWidth - 5, 
                            currentY,
                            durabilityWidth,
                            durabilityHeight
                        };
                    }

                    int itemHeight = std::max(textHeight, durabilityHeight);
                    SDL_Rect equipmentRect = {
                        10 + maxTextTextureWidth + 10,
                        currentY - (padding / 2),
                        renderTargetW - maxTextTextureWidth - 25,
                        itemHeight + (itemHeight + padding) / 2 + borderThickness
                    };

                    if (isMouseHovering(equipmentRect, renderTargetX)) {
                        SDL_SetRenderDrawColor(renderer, Utils::hoverBackColor.r, Utils::hoverBackColor.g, Utils::hoverBackColor.b, 255);
                        SDL_RenderFillRect(renderer, &equipmentRect);
                        UiManager::instance().triggerRenderItemSubMenu(item);
                    }

                    SDL_RenderCopy(renderer, itemNameTextTexture, nullptr, &equipmentSlotRect);
                    SDL_DestroyTexture(itemNameTextTexture);

                    // Render the durability texture if it exists
                    if (hasDurability && durabilityTexture) {
                        SDL_RenderCopy(renderer, durabilityTexture, nullptr, &durabilityRect);
                        SDL_DestroyTexture(durabilityTexture);
                    }

                    //=================
                    // Input Listeners
                    //=================
                    
                    // TODO: Correclty remove and drop item
                    if (InputManager::instance().isKeyPressed(SDLK_a) && isMouseHovering(equipmentRect, renderTargetX)) {
                        InputManager::instance().deactivateKey(SDLK_a);
                        bool isDrop = MapManager::instance().dropItem(player->getXPosition(), player->getYPosition(), item);
                        if (isDrop) {
                            player->removeItemFromInventory(item, true);
                        }
                    }

                    if (InputManager::instance().isLeftClicked() && isMouseHovering(equipmentRect, renderTargetX)) {
                        player->unequipItem(item);
                        InputManager::instance().deactivateLeftClick();
                        UiManager::instance().renderInventoryMenu();
                    }   
                }
            }
        } else {
            throw std::runtime_error("Error, textTexture unknown. (EquipmentMenu)");
        }  

        // SDL_SetRenderDrawColor(renderer, Utils::hpFillColor.r, Utils::hpFillColor.g, Utils::hpFillColor.b, Utils::hpFillColor.a);
        // SDL_RenderFillRect(renderer, &equipmentSlotRect);
    
       currentY += textHeight + padding;
    }

}

void EquipmentMenu::initializeTextureToSlotMap() {
    textureToSlotMap[lhTextTexture] = [](Player* player) { return player->getLeftHand(); };
    textureToSlotMap[rhTextTexture] = [](Player* player) { return player->getRightHand(); };
    textureToSlotMap[headTextTexture] = [](Player* player) { return player->getHead(); };
    textureToSlotMap[torsoTextTexture] = [](Player* player) { return player->getTorso(); };
    textureToSlotMap[handTextTexture] = [](Player* player) { return player->getHands(); };
    textureToSlotMap[footTextTexture] = [](Player* player) { return player->getBoots(); };
    textureToSlotMap[ringTextTexture] = [](Player* player) { return player->getRing1(); };
    textureToSlotMap[ring2TextTexture] = [](Player* player) { return player->getRing2(); };
    textureToSlotMap[amuletTextTexture] = [](Player* player) { return player->getAmulet(); };
}

EquipmentMenu::~EquipmentMenu() {
    // Clean up textures
    SDL_DestroyTexture(headerTextTexture);
    SDL_DestroyTexture(lhTextTexture);
    SDL_DestroyTexture(rhTextTexture);
    SDL_DestroyTexture(headTextTexture);
    SDL_DestroyTexture(torsoTextTexture);
    SDL_DestroyTexture(handTextTexture);
    SDL_DestroyTexture(footTextTexture);
    SDL_DestroyTexture(ringTextTexture);
    SDL_DestroyTexture(ring2TextTexture);
    SDL_DestroyTexture(amuletTextTexture);
}