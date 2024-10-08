#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "../Game/GameManager.h"

#include "../../Menu/StatusMenu.h"
#include "../../Menu/EquipmentMenu.h"
#include "../../Menu/InventoryMenu.h"
#include "../../Menu/ConsoleMenu.h"
#include "../../Menu/DialogMenu.h"
#include "../../Menu/ItemMenu.h"
#include "../../Menu/CharacterMenu.h"
#include "../../Menu/SpellMenu.h"

class UiManager
{   
public:
    static UiManager& instance() {
        static UiManager instance;
        return instance;
    }
    
    const SDL_Rect& getConsoleRect() const;
    const SDL_Rect& getGameRect() const;
    const SDL_Rect& getMenuRect() const;

    const SDL_Rect& getStatusRect() const;
    const SDL_Rect& getEquipmentRect() const;
    const SDL_Rect& getInventoryRect() const;

    void initialize(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);

    void renderAllMenus(SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect& mainRect, bool isHovering, bool force);
    
    void renderStatusMenu();
    void renderEquipmentMenu();
    void renderInventoryMenu();

    void renderTriggeredUI();

    void triggerRenderItemSubMenu(Item* item);
    void renderItemSubMenu(Item* item);
    void closeItemMenu();

    void triggerRenderCharacterMenu();
    void renderCharacterMenu();
    void closeCharacterMenu();

    void triggerRenderSpellMenu(Spell* spell);
    void renderSpellSubMenu(Spell* spell);
    void closeSpellMenu();

    void renderConsole(SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect& rect);

    void renderGame(SDL_Renderer* renderer, const SDL_Rect& rect);

    void updateUI(SDL_Renderer* renderer, TTF_Font* font);

    void updateMenu(bool force = false);
    void updateConsole(bool force = false);
    void updateGame(bool force = false);

    void toggleRenderSpellBook();
    bool isRenderingSpellBook() const;
private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    // Data
    bool isInitialize;
    bool areMenusInitialize;
    bool isConsoleInitialize;
    bool isSpellsRendering;

    // Render Targets
    SDL_Texture* consoleTexture;
    SDL_Texture* gameTexture;
    SDL_Texture* menuTexture;

    // Dirty flags
    bool consoleDirty;
    bool gameDirty;
    bool menuDirty;

    // Force
    bool forceConsoleRender;
    bool forceGameRender;
    bool forceMenuRender;

    // Rect
    SDL_Rect consoleRect;
    SDL_Rect gameRect;
    SDL_Rect menuRect;
    SDL_Rect itemRect;

    // Sub Menus Rect
    SDL_Rect statusRect;
    SDL_Rect equipmentRect;
    SDL_Rect inventoryRect;

    // Menus
    StatusMenu* statusMenu;
    EquipmentMenu* equipmentMenu;
    InventoryMenu* inventoryMenu;

    ConsoleMenu* consoleMenu;
    DialogMenu* dialogMenu;

    ItemMenu* itemMenu;
    bool isItemMenuOpen;
    Item* subItem;
    CharacterMenu* characterMenu;
    bool isCharacterMenuOpen;
    SpellMenu* spellMenu;
    bool isSpellMenuOpen;
    Spell* subSpell;

    // Tileset / MAP
    SDL_Texture* tileset = nullptr;

    const int tile_width = 10;    
    const int tile_height = 10;   
    const int tileset_columns = 16; 

    // Map tiles
    std::vector<SDL_Rect> tiles;

    // Methods
    UiManager();
    ~UiManager();

    void updateRects(int windowWidth, int windowHeight);

    bool isMouseHovering(const SDL_Rect& rect) const;

    void loadTileset(SDL_Renderer* renderer, const char* path);
    void initializeTiles();

    // Prevent copying
    UiManager(const UiManager&) = delete;
    UiManager& operator=(const UiManager&) = delete;
};
