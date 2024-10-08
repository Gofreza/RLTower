#include <SDL2/SDL.h>
#include <iostream>

#include "Manager/UI/UiManager.h"
#include "Manager/Characters/CharactersManager.h"
#include "Manager/Localization/LocalizationManager.h"
#include "Manager/Effect/EffectManager.h"
#include "Manager/Item/ItemManager.h"
#include "Manager/Spell/SpellManager.h"
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

    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
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
    int mouseX, mouseY;
    SDL_Event event;

    //=========
    // Player
    //=========
    Player* player = new Player(1000.0f, 100, 0, 100, 100,
                                1, 0, 
                                7, 3, 1, 1, 5, 1);
    CharactersManager::instance().setPlayer(player);

    player->setHp(player->getHp() - 100);

    //=========
    // Managers
    //=========

    Logger::instance();
    LocalizationManager::instance().loadLocalizationFromFile("../res/localization/" + LANGUAGE + "/strings.json");
    EffectManager::instance().loadEffectsFromFile("../res/localization/" + LANGUAGE + "/effects.json");
    ItemManager::instance().loadItemsFromFile("../res/localization/" + LANGUAGE + "/items.json");
    SpellManager::instance().loadSpellsFromFile("../res/localization/" + LANGUAGE + "/spells.json");
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
    player->addItemInInventory(ItemManager::instance().getItem(10));
    player->addItemInInventory(ItemManager::instance().getItem(10));
    player->addItemInInventory(ItemManager::instance().getItem(10));
    player->addItemInInventory(ItemManager::instance().getItem(10));
    player->addItemInInventory(ItemManager::instance().getItem(11));
    player->addItemInInventory(ItemManager::instance().getItem(11));
    player->addItemInInventory(ItemManager::instance().getItem(11));
    // Give spells
    player->addSpellInSpellBook(SpellManager::instance().getSpell(0));

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {

            InputManager::instance().update(event);

            if (event.type == SDL_QUIT) {
                quit = true;
            }

            // DEBUG Click
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // MouseManager::instance().handleLeftClick(event.button.x, event.button.y);
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    player->addItemInInventory(ItemManager::instance().getItem(26));
                    UiManager::instance().updateMenu(true);
                }
            } 

        }

        UiManager::instance().updateUI(renderer, font);
        GameManager::instance().update();

        // Update the screen
        SDL_RenderPresent(renderer);

        SDL_Delay(32); // 16 ~60 FPS
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}