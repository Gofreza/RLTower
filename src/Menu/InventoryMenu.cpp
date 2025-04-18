#include "InventoryMenu.h"
#include "../Manager/UI/UiManager.h"

InventoryMenu::InventoryMenu(SDL_Renderer* renderer, TTF_Font* font) 
: Menu(renderer, font), maxHeaderWidth(0), isRenderingSpells(false)
{
    // No height calculation needed
    padding = 15;
}

void InventoryMenu::render(const SDL_Rect& rect) {
    int textWidth = 0, textHeight = 0;
    Player* player = CharactersManager::instance().getPlayer();

    //===============
    // Render header
    //===============

    SDL_Texture* headerTextTexture;
    if (!isRenderingSpells) {   
        std::string headerText = LocalizationManager::instance().getText("inventory_title");
        headerTextTexture = Utils::loadTextTexture(renderer, font, headerText, Utils::textColor);
    } else {
        if (player->getMana() > 0) {
           std::string headerText = LocalizationManager::instance().getText("spell_title");    
            headerTextTexture = Utils::loadTextTexture(renderer, font, headerText, Utils::textColor);
        } else {
            std::string headerText = LocalizationManager::instance().getText("spell_energy_title");    
            headerTextTexture = Utils::loadTextTexture(renderer, font, headerText, Utils::textColor);
        }
    }

    if (headerTextTexture) {
        SDL_QueryTexture(headerTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        if (maxHeaderWidth < textWidth) {
            maxHeaderWidth = textWidth;
        }
        // Clear the rect
        SDL_Rect clearRect = {
            (rect.w - maxHeaderWidth) / 2, 
            rect.y + padding - 5, 
            maxHeaderWidth,
            textHeight
        };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderFillRect(renderer, &clearRect);
        
        SDL_Rect headerRect = {
            (rect.w - textWidth) / 2, 
            rect.y + padding - 5, 
            textWidth,
            textHeight
        };
        
        SDL_RenderCopy(renderer, headerTextTexture, nullptr, &headerRect);
    }
    SDL_DestroyTexture(headerTextTexture);

    //===================
    // Render max weight
    //===================

    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << player->getWeight();
    std::string weightStr = stream.str();

    const std::string weightText = weightStr + "/" + std::to_string(player->getMaxWeight());
    SDL_Texture* weightTextTexture = Utils::loadTextTexture(renderer, font, weightText, Utils::textColor);
    if (weightTextTexture)
    {
        SDL_QueryTexture(weightTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect weightRect = {
            0 + padding,
            rect.y + padding - 5,
            textWidth,
            textHeight
        };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderFillRect(renderer, &weightRect);
        SDL_RenderCopy(renderer, weightTextTexture, nullptr, &weightRect);
    }
    SDL_DestroyTexture(weightTextTexture);

    //======================
    // Render switch button
    //======================

    SDL_Rect switchButtonRect;
    SDL_Texture* switchTexture;
    if (!isRenderingSpells) {
        std::string switchText = "->";
        switchTexture = Utils::loadTextTexture(renderer, font, switchText, Utils::textColor);
        SDL_QueryTexture(switchTexture, nullptr, nullptr, &textWidth, &textHeight);
        switchButtonRect = {
            rect.w - textWidth - padding, 
            rect.y + padding - 5, 
            textWidth,
            textHeight
        };
    } else {
        std::string switchText = "<-";
        switchTexture = Utils::loadTextTexture(renderer, font, switchText, Utils::textColor);
        SDL_QueryTexture(switchTexture, nullptr, nullptr, &textWidth, &textHeight);
        switchButtonRect = {
            rect.w - textWidth - padding, 
            rect.y + padding - 5, 
            textWidth,
            textHeight
        };
    }

    if (isMouseHovering(switchButtonRect, rect.x)) {
        SDL_SetTextureColorMod(switchTexture, Utils::hoverColor.r, Utils::hoverColor.g, Utils::hoverColor.b);
    } else {
        SDL_SetTextureColorMod(switchTexture, Utils::textColor.r, Utils::textColor.g, Utils::textColor.b);
    }

    // Click Listeners
    if (InputManager::instance().isLeftClicked() && isMouseHovering(switchButtonRect, rect.x)) {
        //isRenderingSpells = !isRenderingSpells;
        UiManager::instance().toggleRenderSpellBook();
        InputManager::instance().deactivateLeftClick();
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &switchButtonRect);
    SDL_RenderCopy(renderer, switchTexture, nullptr, &switchButtonRect);
    SDL_DestroyTexture(switchTexture);

    //==============================
    // Render iventory items/spells
    //==============================

    SDL_Rect inventoryRect = {
        0,
        rect.y + textHeight + padding,
        rect.w,
        rect.h - textHeight - padding
    };

    // Clear the rect
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderFillRect(renderer, &inventoryRect);
    
    UiManager::instance().drawBorder(renderer, inventoryRect, Utils::borderColor);

    // Start rendering from the top of rect
    int currentY = inventoryRect.y + 5;

    if (!isRenderingSpells) {
        // Get the player inventory vector
        std::vector<Item*> playerInventory = player->getInventory();

        // Render inventory items
        for (auto& item : playerInventory) {
            // Load the texture for the item name
            std::string itemName = item->getName();
            SDL_Texture* itemNameTexture = Utils::loadTextTexture(renderer, font, itemName, Utils::textColor);
            
            // Determine durability text (if applicable)
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
            } else if (item->getType() == ItemType::Container) {
                Containers* container = static_cast<Containers*>(item);
                durabilityText = std::to_string(container->getItemsNumberInContainer());
                hasDurability = true;
            }

            SDL_Texture* durabilityTexture = nullptr;
            if (hasDurability) {
                durabilityTexture = Utils::loadTextTexture(renderer, font, durabilityText, Utils::textColor);
            }

            if (itemNameTexture) {
                int itemNameWidth = 0, itemNameHeight = 0;
                SDL_QueryTexture(itemNameTexture, nullptr, nullptr, &itemNameWidth, &itemNameHeight);

                SDL_Rect itemNameRect = {
                    inventoryRect.x + 5, 
                    currentY + 2,
                    itemNameWidth,
                    itemNameHeight
                };

                SDL_Rect durabilityRect = {};
                int durabilityWidth = 0, durabilityHeight = 0;
                if (hasDurability && durabilityTexture) {
                    SDL_QueryTexture(durabilityTexture, nullptr, nullptr, &durabilityWidth, &durabilityHeight);

                    durabilityRect = {
                        inventoryRect.x + inventoryRect.w - durabilityWidth - 5, 
                        currentY + 2,
                        durabilityWidth,
                        durabilityHeight
                    };
                }

                // Define the full item rectangle (itemRect)
                int itemHeight = std::max(itemNameHeight, durabilityHeight) + 5;
                SDL_Rect itemRect = {
                    inventoryRect.x + 5,
                    currentY,
                    inventoryRect.w - 10,
                    itemHeight
                };

                // Update color modulation based on mouse hover
                if (isMouseHovering(itemRect, rect.x)) {
                    SDL_SetRenderDrawColor(renderer, Utils::hoverBackColor.r, Utils::hoverBackColor.g, Utils::hoverBackColor.b, 255);
                    SDL_RenderFillRect(renderer, &itemRect);
                    UiManager::instance().triggerRenderItemSubMenu(item);
                }
                
                // Render the item name texture
                SDL_RenderCopy(renderer, itemNameTexture, nullptr, &itemNameRect);

                // Render the durability texture if it exists
                if (hasDurability && durabilityTexture) {
                    SDL_RenderCopy(renderer, durabilityTexture, nullptr, &durabilityRect);
                    SDL_DestroyTexture(durabilityTexture);
                }

                // Check if the itemRect exceeds the inventory boundaries
                if (currentY + itemNameHeight > inventoryRect.y + inventoryRect.h) {
                    SDL_DestroyTexture(itemNameTexture);
                    break;
                }

                // Update the Y position for the next item
                currentY += itemHeight;

                SDL_DestroyTexture(itemNameTexture);

                //=================
                // Input Listeners
                //=================
                
                if (InputManager::instance().isKeyPressed(SDLK_a) && isMouseHovering(itemRect, rect.x)) {
                    InputManager::instance().deactivateKey(SDLK_a);
                    bool isDrop = MapManager::instance().dropItem(player->getXPosition(), player->getYPosition(), item);
                    if (isDrop) {
                        player->removeItemFromInventory(item, true);
                    }
                }

                if (InputManager::instance().isLeftClicked() && isMouseHovering(itemRect, rect.x)) {
                    player->equipItem(item);
                    InputManager::instance().deactivateLeftClick();
                    UiManager::instance().renderEquipmentMenu();
                    UiManager::instance().renderStatusMenu();
                }
            }
        }

    } else {
        // Get the player spells vector
        std::vector<Spell*> playerSpells = player->getSpells();

        // Render spells
        for (auto& spell : playerSpells) {
            // Load the texture for the item name
            std::string spellName = spell->getName();
            SDL_Texture* spellNameTexture = Utils::loadTextTexture(renderer, font, spellName, Utils::textColor);
            
            if (spellNameTexture)
            {
                int spellNameWidth = 0, spellNameHeight = 0;
                SDL_QueryTexture(spellNameTexture, nullptr, nullptr, &spellNameWidth, &spellNameHeight);

                SDL_Rect itemNameRect = {
                    inventoryRect.x + 5, 
                    currentY + 2,
                    spellNameWidth,
                    spellNameHeight
                };

                // Define the full item rectangle (itemRect)
                SDL_Rect itemRect = {
                    inventoryRect.x + 5,
                    currentY,
                    inventoryRect.w - 10,
                    spellNameHeight + 5
                };

                if (spell->isActive()) {
                    UiManager::instance().drawBorder(renderer, itemRect, Utils::borderColor);
                }

                if (isMouseHovering(itemRect, rect.x)) {
                    SDL_SetRenderDrawColor(renderer, Utils::hoverBackColor.r, Utils::hoverBackColor.g, Utils::hoverBackColor.b, 255);
                    SDL_RenderFillRect(renderer, &itemRect);
                    UiManager::instance().triggerRenderSpellMenu(spell);
                }

                SDL_RenderCopy(renderer, spellNameTexture, nullptr, &itemNameRect);

                currentY += spellNameHeight + 5;

                SDL_DestroyTexture(spellNameTexture);

                //=================
                // Input Listeners
                //=================

                if (InputManager::instance().isLeftClicked() && isMouseHovering(itemRect, rect.x)) {
                    InputManager::instance().deactivateLeftClick();
                    GameManager::instance().stopCombatMode();
                    player->setCurrentActiveSpell(spell);
                }
            }
        }
    }
     
}

void InventoryMenu::toggleSpellsRendering() {
    isRenderingSpells = !isRenderingSpells;
}

int InventoryMenu::getHeight() const {
    // Take all remaining space
    return -1;
}

InventoryMenu::~InventoryMenu() {}