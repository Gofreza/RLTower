#include <SDL2/SDL.h>
#include <iostream>

#include "Manager/Config/Config.h"
#include "Manager/UI/UiManager.h"
#include "Manager/Characters/CharactersManager.h"
#include "Manager/Localization/LocalizationManager.h"
#include "Manager/Effect/EffectManager.h"
#include "Manager/Item/ItemManager.h"
#include "Manager/Spell/SpellManager.h"
#include "Manager/Characters/EnemyManager.h"
#include "Manager/Controls/InputManager.h"
#include "Manager/Game/GameManager.h"
#include "Misc/Utils.h"
#include "Misc/Logger.h"
#include "Character/Player.h"

static std::string LANGUAGE = "en";

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("RLTower",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = nullptr;
    if (!Utils::initSDL_TTF(font, "../res/fonts/PressStart2P-Regular.ttf", 10)) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event event;
    //=========
    // Config
    //=========
    Config& config = Config::instance();
    config.setDebugMode(false);
    config.setShowFps(true);
    config.setArenaMode(false);

    //=========
    // Player
    //=========
    Player* player = new Player("Player", {55, 55, 160, 255}, GroupType::Player, "tortueachapeau.png", "Tortue à chapeau",
                                1000.0f, 100, 0, 100, false, 5, 100,
                                // Physical damage && Magical damage
                                1, 0, 
                                7, 3, 5, 1, 5, 1,
                                '@',
                                std::vector<int>{}, std::vector<int>{});
    CharactersManager::instance().setPlayer(player);

    player->setHp(player->getHp());

    //=========
    // Managers
    //=========

    Logger::instance();
    LocalizationManager::instance().loadLocalizationFromFile("../res/localization/" + LANGUAGE + "/strings.json");
    EffectManager::instance().loadEffectsFromFile("../res/localization/" + LANGUAGE + "/effects.json");
    ItemManager::instance().loadItemsFromFile("../res/localization/" + LANGUAGE + "/items.json");
    SpellManager::instance().loadSpellsFromFile("../res/localization/" + LANGUAGE + "/spells.json");
    EnemyManager::instance().loadEnemiesFromFile("../res/localization/" + LANGUAGE + "/enemies.json");
    GameManager::instance().initialize();
    UiManager::instance().initialize(window, renderer, font);

    //=========
    // CHEATS
    //=========
    // Give items
    player->addItemInInventory(ItemManager::instance().getItem(1));
    player->addItemInInventory(ItemManager::instance().getItem(3));
    player->addItemInInventory(ItemManager::instance().getItem(23));
    player->addItemInInventory(ItemManager::instance().getItem(22));
    player->addItemInInventory(ItemManager::instance().getItem(5));
    player->addItemInInventory(ItemManager::instance().getItem(6));
    player->addItemInInventory(ItemManager::instance().getItem(7));
    player->addItemInInventory(ItemManager::instance().getItem(8));
    player->addItemInInventory(ItemManager::instance().getItem(9));
    player->addItemInInventory(ItemManager::instance().getItem(15));
    player->addItemInInventory(ItemManager::instance().getItem(16));
    player->addItemInInventory(ItemManager::instance().getItem(21));
    player->addItemInInventory(ItemManager::instance().getItem(12));
    player->addItemInInventory(ItemManager::instance().getItem(12));
    player->addItemInInventory(ItemManager::instance().getItem(12));
    // player->addItemInInventory(ItemManager::instance().getItem(10));
    // player->addItemInInventory(ItemManager::instance().getItem(10));
    // player->addItemInInventory(ItemManager::instance().getItem(10));
    // player->addItemInInventory(ItemManager::instance().getItem(10));
    // player->addItemInInventory(ItemManager::instance().getItem(11));
    // player->addItemInInventory(ItemManager::instance().getItem(11));
    // player->addItemInInventory(ItemManager::instance().getItem(11));
    player->addItemInInventory(ItemManager::instance().getItem(26));
    player->addItemInInventory(ItemManager::instance().getItem(24));
    // Give spells
    player->addSpellInSpellBook(SpellManager::instance().getSpell(0));
    player->addSpellInSpellBook(SpellManager::instance().getSpell(1));
    player->addSpellInSpellBook(SpellManager::instance().getSpell(2));
    player->addSpellInSpellBook(SpellManager::instance().getSpell(3));
    player->addSpellInSpellBook(SpellManager::instance().getSpell(4));
    player->addSpellInSpellBook(SpellManager::instance().getSpell(5));
    player->addSpellInSpellBook(SpellManager::instance().getSpell(6));

    //=========
    // FPS
    //=========
    Uint32 lastTime = SDL_GetTicks(); // Time of the last frame
    Uint32 fpsCounterLastUpdate = lastTime;
    int frameCount = 0; // Count frames
    float currentFPS = 0.0f;

    const int TARGET_FPS = 144;
    const int FRAME_DELAY = 1000 / TARGET_FPS; // Target frame time in milliseconds

    Uint32 frameStart, frameTime;

    while (!quit) {
        frameStart = SDL_GetTicks();

        if (config.isShowFps()) {
            Uint32 currentTime = SDL_GetTicks();
            // Uint32 deltaTime = currentTime - lastTime; // Time elapsed since the last frame
            lastTime = currentTime;

            // Calculate FPS
            frameCount++;
            if (currentTime - fpsCounterLastUpdate >= 1000) { // Update every 1 second
                currentFPS = frameCount / ((currentTime - fpsCounterLastUpdate) / 1000.0f);
                frameCount = 0;
                fpsCounterLastUpdate = currentTime;
            }
        }
        
        while (SDL_PollEvent(&event) != 0) {

            InputManager::instance().update(event);

            if (event.type == SDL_QUIT) {
                quit = true;
            }

            // DEBUG Click
            if (config.isDebugMode() && event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Logger::instance().info("This is a pretty long message used to debug the multi-line print in the console.");
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    if (player->isCharacterAuraUser()) {
                        player->setCharacterAuraUser(false);
                        player->setMana(100);
                        player->setMaxMana(100);
                        player->setEnergy(0);
                        player->setMaxEnergy(0);
                    } else {
                        player->setCharacterAuraUser(true);
                        player->setMana(0);
                        player->setMaxMana(0);
                        player->setEnergy(100);
                        player->setMaxEnergy(100);
                    }
                    player->addItemInInventory(ItemManager::instance().getItem(10));
                    UiManager::instance().updateMenu(true);
                }
            } 

        }

        UiManager::instance().updateUI(renderer, font);
        GameManager::instance().update();
        if (config.isShowFps()) {
            UiManager::instance().renderFps(currentFPS);
        }

        // Update the screen
        SDL_RenderPresent(renderer);

        // Delete deferred items
        ItemManager::instance().deleteDeferredItems();

        // Calculate frame time and adjust delay
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime); // Delay to match target frame time
        }
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}