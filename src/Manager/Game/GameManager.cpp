#include "GameManager.h"
#include "../../Misc/Utils.h"
#include "../../Misc/RandomUtils.h"
#include <queue>

GameManager::GameManager():   
    player(CharactersManager::instance().getPlayer()),
    turn(0), numberOfCharactersThatPlayedThisTurn(0),
    combatMode(false), spellMode(false), cacMode(false)
{
}

void GameManager::initialize()
{   
    // Initialize the map
    MapManager::instance().initialize();
    MapManager::instance().generateMap(100, 100, 5);
    MapManager::instance().addPlayer(player);

    // Add enemies
    EnemyManager::instance().initialize(this->enemies, 1, 10);
    
    // Put enemies in the map
    MapManager::instance().addEnemies(this->enemies);

    std::cout << "Map generated" << std::endl;
}

void GameManager::update()
{   
    playTurn();

    // TODO: When changing floor, clear the deferred deletions vector
}

void GameManager::playTurn() {
    if (characters.empty()) {
        // Add all characters to the priority queue
        characters.reserve(1 + npcs.size() + enemies.size());
        characters.push_back(player);
        for (auto& npc : npcs) {
            characters.push_back(npc);
        }
        for (auto& enemy : enemies) {
            characters.push_back(enemy);
        }
        std::sort(characters.begin(), characters.end(), [](Character* a, Character* b) {
            return a->getSpeed() > b->getSpeed();
        });
        this->currentCharacterIndex = 0;
    }

    // Check the top characters and see if he has played
    Character* character = characters[currentCharacterIndex];
    bool hasPlay = character->update();

    // Check if character is dead
    if (character->getHp() <= 0) {
        std::cout << character->getName() << " is dead" << std::endl;
        // Remove the character from the map
        MapManager::instance().removeCharacter(character->getXPosition(), character->getYPosition());
        // Remove it from the vector
        characters.erase(characters.begin() + currentCharacterIndex);
        if (currentCharacterIndex >= characters.size()) {
            currentCharacterIndex = 0; // Wrap back to start if necessary
        }
        // Free the character
        this->addCharacterToDefferedDeletions(character);
    } else {
        if (hasPlay) {
            numberOfCharactersThatPlayedThisTurn++;
            currentCharacterIndex = (currentCharacterIndex + 1) % characters.size();
        }
    }

    // When all characters have played
    if (numberOfCharactersThatPlayedThisTurn >= characters.size()) {
        // Update turn
        turn++;
        // Update cell's effects
        for (auto& cell : cellsAffectedByEffects) {
            cell->updateEffects();
        }
        numberOfCharactersThatPlayedThisTurn = 0;
    }
}

void GameManager::renderMap(SDL_Renderer* renderer, const SDL_Rect& rect, SDL_Texture* tileset, const std::vector<SDL_Rect>& tiles)
{
    const auto& ascii_map = MapManager::instance().getAsciiMap();
    const int map_width = ascii_map[0].size();
    const int map_height = ascii_map.size();

    // Calculate the field of view here to update the visibility if change in fov happened
    MapManager::instance().calculateFov(player);

    int player_x = player->getXPosition(); 
    int player_y = player->getYPosition();

    int player_attack_range = player->getRange();
    if (spellMode && player->getCurrentActiveSpell() != nullptr) {
        player_attack_range = player->getCurrentActiveSpell()->getRange();
    } 

    // Obtenez le temps actuel
    Uint32 current_time = SDL_GetTicks();

    // Déterminez si la couleur doit être inversée
    bool is_flashing = (current_time / 500) % 2 == 0;

    const int tile_size = 20;

    // Calculate half the screen size in tiles (integer tiles)
    int half_width_in_tiles = rect.w / (2 * tile_size);
    int half_height_in_tiles = rect.h / (2 * tile_size);

    // Start rendering from the map coordinates based on player position, keeping the player in the center
    int start_x = player_x - half_width_in_tiles;
    int start_y = player_y - half_height_in_tiles;

    for (int y = 0; y < rect.h / tile_size; y++) {
        for (int x = 0; x < rect.w / tile_size; x++) {
            int map_x = start_x + x;
            int map_y = start_y + y;

            // Ensure the map coordinates are within bounds
            if (map_x >= 0 && map_x < map_width && map_y >= 0 && map_y < map_height) {
                SDL_Rect dest;
                dest.x = x * tile_size;
                dest.y = y * tile_size;
                dest.w = tile_size;
                dest.h = tile_size;

                SDL_Rect src = tiles[0];
                Cell cell = ascii_map[map_y][map_x];

                if (!cell.isExplored) {
                    // Render a dark cell
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &dest);
                } else {
                    // TODO: Swich from char to int to access directly the tile
                    // char tile_char = cell.getSymbol();
                    // int ascii_value = static_cast<int>(tile_char);

                    // src = tiles[ascii_value];

                    if (cell.isInSight) {
                        // Change the color of the src
                        SDL_SetTextureColorMod(tileset, cell.currentColor.r, cell.currentColor.g, cell.currentColor.b); 
                        // Set background color to light gray
                        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);

                        src = tiles[static_cast<int>(cell.getSymbol())];
                    } else {
                        // Change the color of the src
                        SDL_SetTextureColorMod(tileset, 100, 100, 100);
                        // Set background color to default
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

                        src = tiles[static_cast<int>(cell.getLastSeenSymbol())];
                    }

                    // Render the background
                    SDL_RenderFillRect(renderer, &dest);

                    // Highlight cells in combat mode
                    // TODO: Maybe switch with something else
                    if (combatMode) {
                        int dx = map_x - player_x;
                        int dy = map_y - player_y;
                        int distance = sqrt(dx * dx + dy * dy);

                        if (distance <= player_attack_range) {
                            SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

                            // Calculate pulsing alpha value
                            Uint32 time = SDL_GetTicks();
                            Uint8 alpha = static_cast<Uint8>((sin(time * 0.003) + 1) * 127.5); // Pulses between 0 and 255

                            SDL_SetRenderDrawColor(renderer, 100, 10, 10, alpha);
                            SDL_RenderFillRect(renderer, &dest);
                            SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_NONE);
                        }
                    }

                    // Render the tile
                    SDL_RenderCopy(renderer, tileset, &src, &dest);
                } 

                // ============
                // Listeners
                // ============
                
                if (Utils::isMouseHovering(dest, rect.x, rect.y)) {
                    if (combatMode) {
                        SDL_Color color = Utils::borderColor;
                        if (spellMode) {
                            color = Utils::magCombatColor;
                        } else {
                            color = Utils::phyCombatColor;
                        }
                        UiManager::instance().drawBorder(renderer, dest, color);
                    } else {
                        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
                        SDL_RenderFillRect(renderer, &dest);
                        SDL_RenderCopy(renderer, tileset, &src, &dest);
                    }
                    
                    Cell &cell = MapManager::instance().getCell(map_x, map_y);
                    if (cell.hasItem()) {
                        UiManager::instance().triggerRenderItemDialog(cell.getItem());
                        // Pickup item
                        if (InputManager::instance().isLeftClicked() && Utils::distance(player_x, player_y, map_x, map_y) <= 1.5) {
                            InputManager::instance().deactivateLeftClick();
                            player->addItemInInventory(cell.takeItem());
                            UiManager::instance().updateMenu(true);
                            UiManager::instance().updateGame(true);
                        }
                    } else if (cell.hasCharacter()) {
                        UiManager::instance().triggerRenderCharacterDialog(cell.getCharacter());
                    } else {
                        UiManager::instance().updateConsole(true);
                    }

                    // Attack
                    if (combatMode) {
                        // Add 0.5 to the range to allow diagonal attacks
                        float diag = player_attack_range + 0.5;
                        if (InputManager::instance().isLeftClicked() 
                            && Utils::distance(player_x, player_y, map_x, map_y) <= diag
                            && (cell.hasCharacter() || InputManager::instance().isDoubleClicked())) {
                                InputManager::instance().deactivateLeftClick();
                                InputManager::instance().deactivateDoubleClick();
                                player->attack(cell, cellsAffectedByEffects);
                                UiManager::instance().updateMenu(true);
                        }
                    }
                }    
            }
        }
    }
}

bool GameManager::movePlayer() {
    bool moved = false;
    if (InputManager::instance().isKeyPressed(Config::instance().getUpKey())) {
        InputManager::instance().deactivateKey(Config::instance().getUpKey());

        if (MapManager::instance().canPlayerMove(player, 0, -1)) {
            player->move(0, -1);
            MapManager::instance().movePlayerInMap(player, 0, -1);  
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(Config::instance().getDownKey())) {
        InputManager::instance().deactivateKey(Config::instance().getDownKey());

        if (MapManager::instance().canPlayerMove(player, 0, 1)) {
            player->move(0, 1);
            MapManager::instance().movePlayerInMap(player, 0, 1);
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(Config::instance().getLeftKey())) {
        InputManager::instance().deactivateKey(Config::instance().getLeftKey());

        if (MapManager::instance().canPlayerMove(player, -1, 0)) {
            player->move(-1, 0);
            MapManager::instance().movePlayerInMap(player, -1, 0);
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(Config::instance().getRightKey())) {
        InputManager::instance().deactivateKey(Config::instance().getRightKey());

        if (MapManager::instance().canPlayerMove(player, 1, 0)) {
            player->move(1, 0);
            MapManager::instance().movePlayerInMap(player, 1, 0);
            moved = true;
        }
    }
    if (moved) {
        UiManager::instance().updateGame(true);
    }
    return moved;
}

void GameManager::moveCharacter(Character* character, int dx, int dy) {
    if (MapManager::instance().canCharacterMove(character, dx, dy)) {
        character->move(dx, dy);
        MapManager::instance().moveCharacterInMap(character, dx, dy);
    }
}

void GameManager::toggleCombatMode() {
    if (spellMode) {
        spellMode = false;
        cacMode = true;
    } else {
        if (cacMode) {
            cacMode = false;
            combatMode = false;
        } else {
            combatMode = true;
            Item* w = player->getWeapon();
            if (w) {
                Weapon* weapon = static_cast<Weapon*>(w);
                WeaponType weaponType = weapon->getWeaponType();
                if ((weaponType == WeaponType::Staff && player->getCurrentActiveSpell() != nullptr) ||
                    (player->getCurrentActiveSpell() != nullptr && player->getCurrentActiveSpell()->getSpellEnergyType() == SpellEnergy::Energy)) {
                    spellMode = true;
                } else {
                    cacMode = true;
                }
            } else {
                cacMode = true;
            }
        }   
    }    
}

void GameManager::stopCombatMode() {
    combatMode = false;
    spellMode = false;
    cacMode = false;
}

void GameManager::addCharacterToDefferedDeletions(Character* character) {
    deferredDeletions.push_back(character);
}

void GameManager::deleteDeferredCharacters() {
    for (auto& character : deferredDeletions) {
        delete character;
    }
    deferredDeletions.clear();
}

GameManager::~GameManager()
{
    for (auto& character : deferredDeletions) {
        std::cout << "Deleting character: " << character << std::endl;
        delete character;
    }
    deferredDeletions.clear();
    cellsAffectedByEffects.clear();
}
