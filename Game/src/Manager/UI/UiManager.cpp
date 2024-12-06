#include "UiManager.h"
#include <iostream>
#include <stdexcept>

UiManager::UiManager() 
: isInitialize(false), areMenusInitialize(false), isConsoleInitialize(false), isSpellsRendering(false),
  consoleDirty(true), gameDirty(true), menuDirty(true),
  isInConsole(false), isInGame(false), isInMenu(false),
  forceConsoleRender(false), forceGameRender(false), forceMenuRender(false),
  isItemMenuOpen(false), isCharacterMenuOpen(false), isSpellMenuOpen(false)
{}

void UiManager::initialize(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    if (!isInitialize)
    {
        this->renderer = renderer;
        this->font = font;
        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        // Create rects
        updateRects(windowWidth, windowHeight);

        // Create render targets
        consoleTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, consoleRect.w, consoleRect.h);
        gameTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gameRect.w, gameRect.h);
        menuTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, menuRect.w, menuRect.h);

        // Load the tileset
        loadTileset(renderer, "../res/tilesets/Potash_10x10.png");
        initializeTiles();

        isInitialize = true;
    }
    else {
        std::cout << "UiManager already initialized !" << std::endl;
    }
}

//==================
// UPDATES
//==================

void UiManager::updateRects(int windowWidth, int windowHeight) {
    consoleRect = {
        0,
        0, 
        static_cast<int>(windowWidth * 0.70),  // 70% of window width
        static_cast<int>(windowHeight * 0.20)  // 20% of window height
    };

    gameRect = {
        0,
        static_cast<int>(windowHeight * 0.20),
        static_cast<int>(windowWidth * 0.70),  // 70% of window width
        static_cast<int>(windowHeight * 0.80)  // 80% of window height
    };

    menuRect = {
        static_cast<int>(windowWidth * 0.70), // Start at 70% of window width
        0,
        static_cast<int>(windowWidth * 0.30), // 30% of window width
        windowHeight                          // 100% of window height
    };

    itemRect = {
        static_cast<int>(windowWidth * 0.35), // consoleRect.w / 2
        0,
        static_cast<int>(windowWidth * 0.35), // consoleRect.w / 2
        windowHeight
    };
}

void UiManager::updateUI(SDL_Renderer* renderer, TTF_Font* font) {
    // Reset hover states
    if (isMouseHovering(consoleRect)) {
        if (this->isInGame || this->isInMenu) {
            resetRectsDisplay();
        }
        this->isInConsole = true;
    } else if (isMouseHovering(gameRect)) {
        if (this->isInConsole || this->isInMenu) {
            resetRectsDisplay();
        }
        this->isInGame = true;
    } else if (isMouseHovering(menuRect)) {
        if (this->isInConsole || this->isInGame) {
            resetRectsDisplay();
        }
        this->isInMenu = true;
    }

    // Update console area if dirty
    if (consoleDirty) {
        //std::cout << "Console is behin updated" << std::endl;

        SDL_ClearError();
        SDL_SetRenderTarget(renderer, consoleTexture);
        if (SDL_GetError()[0] != '\0') {
            std::cerr << "Failed to set console render target! SDL_Error: " << SDL_GetError() << std::endl;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Green background
        SDL_RenderClear(renderer); // Clear the texture with green

        // Render console
        renderConsole(renderer, font, consoleRect);

        // Reset render target to default (window)
        SDL_SetRenderTarget(renderer, nullptr);
        consoleDirty = false; // Mark as clean
    }

    // Update game area if dirty
    if (gameDirty || isMouseHovering(gameRect)) {
        //std::cout << "Game is behin updated" << std::endl;
        
        SDL_ClearError();
        SDL_SetRenderTarget(renderer, gameTexture);
        if (SDL_GetError()[0] != '\0') {
            std::cerr << "Failed to set game render target! SDL_Error: " << SDL_GetError() << std::endl;
        }    
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Red for game area
        SDL_RenderFillRect(renderer, nullptr); // Fill the game texture

        // Render game
        renderGame(renderer, gameRect);

        SDL_SetRenderTarget(renderer, nullptr);
        gameDirty = false; // Mark as clean
    }

    // Update menu area if dirty
    if (menuDirty || isMouseHovering(menuRect)) {
        //std::cout << "Menu is behin updated" << std::endl;
        
        SDL_ClearError();
        SDL_SetRenderTarget(renderer, menuTexture);
        if (SDL_GetError()[0] != '\0') {
            std::cerr << "Failed to set menu render target! SDL_Error: " << SDL_GetError() << std::endl;
        }
        // Do not clear renderer only update what is necessary
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear with black or any background color
        // SDL_RenderClear(renderer); // Clear the previous content

        renderAllMenus(renderer, font, menuRect, isMouseHovering(menuRect), forceMenuRender); // Render all menus into this texture
        SDL_SetRenderTarget(renderer, nullptr);
        menuDirty = false; // Mark as clean
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Render the console, game, and menu textures
    SDL_RenderCopy(renderer, consoleTexture, nullptr, &consoleRect);
    SDL_RenderCopy(renderer, gameTexture, nullptr, &gameRect);
    SDL_RenderCopy(renderer, menuTexture, nullptr, &menuRect);

    // Render triggered menu
    renderTriggeredUI();
}

void UiManager::updateConsole(bool force) {
    consoleDirty = true;
}

void UiManager::updateGame(bool force) {
    gameDirty = true;
}

void UiManager::updateMenu(bool force) {
    statusMenu->updateHp();
    statusMenu->updateMana();
    statusMenu->updateGold();
    statusMenu->updateSilver();
    statusMenu->updateCopper();
    menuDirty = true;
    forceMenuRender = true;
}

//==================
// HOVER
//==================

bool UiManager::isMouseHovering(const SDL_Rect& rect) const {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return mouseX >= rect.x && mouseX <= rect.x + rect.w &&
           mouseY >= rect.y && mouseY <= rect.y + rect.h;
}

void UiManager::resetRectsDisplay() {
    if (this->isInConsole) {
        consoleDirty = true;
        this->isInConsole = false;
    }
    else if (this->isInGame) {
        gameDirty = true;
        this->isInGame = false;
    }
    else if (this->isInMenu) {
        menuDirty = true;
        this->isInMenu = false;
    }
}

//==================
// GETTERS
//==================

const SDL_Rect& UiManager::getConsoleRect() const {
    if (isInitialize)
    {
        return this->consoleRect;
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }
}

const SDL_Rect& UiManager::getGameRect() const {
    if (isInitialize)
    {
        return this->gameRect;
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }
}

const SDL_Rect& UiManager::getMenuRect() const {
    if (isInitialize)
    {
        return this->menuRect;
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }
}

const SDL_Rect& UiManager::getStatusRect() const {
    if (isInitialize)
    {
        return this->statusRect;
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }
}

const SDL_Rect& UiManager::getEquipmentRect() const {
    if (isInitialize)
    {
        return this->equipmentRect;
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }
}

const SDL_Rect& UiManager::getInventoryRect() const {
    if (isInitialize)
    {
        return this->inventoryRect;
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }
}

//==================
// MENUS
//==================

void UiManager::renderAllMenus(SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect& mainRect, bool isHovering, bool force) {
    
    if(isInitialize) {
        if (!areMenusInitialize) {
            // Instantiate menus
            statusMenu = new StatusMenu(renderer, font);
            equipmentMenu = new EquipmentMenu(renderer, font);
            inventoryMenu = new InventoryMenu(renderer, font);
            itemMenu = new ItemMenu(renderer, font);
            characterMenu = new CharacterMenu(renderer, font);
            spellMenu = new SpellMenu(renderer, font);
            std::cout << "Menu initialized" << std::endl;
            areMenusInitialize = true;
        } 

        // Calculate heights
        int statusHeight = statusMenu->getHeight();
        int equipmentHeight = equipmentMenu->getHeight();
        int remainingHeight = mainRect.h - (statusHeight + equipmentHeight);

        // Define rects for each menu
        statusRect = {mainRect.x, mainRect.y, mainRect.w, statusHeight};
        equipmentRect = {mainRect.x, mainRect.y + statusHeight, mainRect.w, equipmentHeight};
        inventoryRect = {mainRect.x, mainRect.y + statusHeight + equipmentHeight, mainRect.w, remainingHeight};

        // Render each menu
        if (!isHovering || force) {
            statusMenu->render(statusRect);
            equipmentMenu->render(equipmentRect);
            inventoryMenu->render(inventoryRect); 
            if (force) {
                force = false;
            }       
        } else {
            // Check where the mouse is
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (mouseX >= statusRect.x && mouseX < statusRect.x + statusRect.w &&
                mouseY >= statusRect.y && mouseY < statusRect.y + statusRect.h) {
                //std::cout << "Hovering status area" << std::endl;
                statusMenu->render(statusRect);
            }
            else if(mouseX >= equipmentRect.x && mouseX < equipmentRect.x + equipmentRect.w &&
                    mouseY >= equipmentRect.y && mouseY < equipmentRect.y + equipmentRect.h) {
                //std::cout << "Hovering equipment area" << std::endl;
                equipmentMenu->render(equipmentRect);
            }
            else if(mouseX >= inventoryRect.x && mouseX < inventoryRect.x + inventoryRect.w &&
                    mouseY >= inventoryRect.y && mouseY < inventoryRect.y + inventoryRect.h) {
                //std::cout << "Hovering inventory area" << std::endl;
                inventoryMenu->render(inventoryRect);           
            }   
        }
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }   
}

void UiManager::renderStatusMenu() {
    if (isInitialize) {
        statusMenu->render(statusRect);
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }  
}

void UiManager::renderEquipmentMenu() {
    if (isInitialize) {
        equipmentMenu->render(equipmentRect);
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }  
}

void UiManager::renderInventoryMenu() {
    if (isInitialize) {
        inventoryMenu->render(inventoryRect);
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }
}

void UiManager::renderTriggeredUI() {
    if (isItemMenuOpen) {        
        renderItemSubMenu(subItem);
    } else if (isCharacterMenuOpen) {
        renderCharacterMenu();
    } else if (isSpellMenuOpen) {
        renderSpellSubMenu(subSpell);
    }

    closeItemMenu();
    closeCharacterMenu();
    closeSpellMenu();
}

//===========
// Item Menu
//===========

void UiManager::triggerRenderItemSubMenu(Item* item) {
    isItemMenuOpen = true;
    subItem = item;
}

void UiManager::renderItemSubMenu(Item* item) {
    // Clear rect
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &itemRect);

    // Render item sub-menu
    itemMenu->render(itemRect, item);
}

void UiManager::closeItemMenu() {
    isItemMenuOpen = false;
}

//================
// Character menu
//================

void UiManager::triggerRenderCharacterMenu() {
    isCharacterMenuOpen = true;
}

void UiManager::renderCharacterMenu() {
    // Clear rect
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &itemRect);

    characterMenu->render(itemRect);
}

void UiManager::closeCharacterMenu() {
    isCharacterMenuOpen = false;
}

//============
// Spell menu
//============

void UiManager::triggerRenderSpellMenu(Spell* spell) {
    isSpellMenuOpen = true;
    subSpell = spell;
}

void UiManager::renderSpellSubMenu(Spell* spell) {
    // Clear rect
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &itemRect);

    spellMenu->render(itemRect, spell);
}

void UiManager::closeSpellMenu() {
    isSpellMenuOpen = false;
}

void UiManager::toggleRenderSpellBook() {
    isSpellsRendering = !isSpellsRendering;
    inventoryMenu->toggleSpellsRendering();
    menuDirty = true;
}

bool UiManager::isRenderingSpellBook() const {
    return isSpellsRendering;
}

//==================
// CONSOLE
//==================

void UiManager::renderConsole(SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect& rect) {
    if (isInitialize) {
        if (!isConsoleInitialize) {
            consoleMenu = new ConsoleMenu(renderer, font);
            dialogMenu = new DialogMenu(renderer, font);
            std::cout << "Console initialized" << std::endl;
            isConsoleInitialize = true;
        }

        // Get the width
        int menuWidth = rect.w / 2;

        // Define the rects
        SDL_Rect consoleRect = {rect.x, rect.y, menuWidth, rect.h};
        SDL_Rect dialogRect = {rect.x + menuWidth, rect.y, menuWidth, rect.h};

        // Render the menus
        consoleMenu->render(consoleRect);
        dialogMenu->render(dialogRect);
        
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }
}

//==================
// GAME
//==================

void UiManager::renderGame(SDL_Renderer* renderer, const SDL_Rect& rect) {
    if (isInitialize) {
        // Clear the game area
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderFillRect(renderer, nullptr);

        // Render the map
        GameManager::instance().renderMap(renderer, rect, tileset, tiles);
    } else {
        throw std::runtime_error("UiManager is not initialized.");
    }
}

//==================
// TILESET
//==================

void UiManager::loadTileset(SDL_Renderer* renderer, const char* path) {
    // Load the tileset image (PNG in this case)
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        std::cerr << "Failed to load tileset: " << IMG_GetError() << std::endl;
        return;
    }

    // Set the color key for transparency (magenta in this case)
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

    // Create a texture from the surface
    if (tileset) {
        SDL_DestroyTexture(tileset);
    }
    tileset = SDL_CreateTextureFromSurface(renderer, surface);
    if (!tileset) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Free the surface
    SDL_FreeSurface(surface);
}


// Function to initialize the tiles array
void UiManager::initializeTiles() {
    tiles.resize(256); // Resize the vector to hold 256 tiles
    for (int i = 0; i < 256; i++) {
        int x = (i % tileset_columns) * tile_width;
        int y = (i / tileset_columns) * tile_height;
        
        // Store the rectangle representing the tile in the tileset
        tiles[i].x = x;
        tiles[i].y = y;
        tiles[i].w = tile_width;
        tiles[i].h = tile_height;
    }
}

//==================
// FPS
//==================

void UiManager::renderFps(float fps) {
    // Render the FPS
    SDL_Color color = {100, 100, 100, 255};
    std::string fpsText = std::to_string(static_cast<int>(fps * 10) / 10.0).substr(0, 4);
    SDL_Surface* surface = TTF_RenderText_Solid(font, fpsText.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Get the width and height of the text
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    // Set the destination rect
    SDL_Rect dest = {0, 0, width, height};

    // Render the text
    SDL_RenderCopy(renderer, texture, nullptr, &dest);

    // Free the surface and texture
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

//==================
// DESTRUCTOR
//==================

UiManager::~UiManager() {
    SDL_DestroyTexture(consoleTexture);
    SDL_DestroyTexture(gameTexture);
    SDL_DestroyTexture(menuTexture);

    if (statusMenu)
        delete(statusMenu);
    if (equipmentMenu)
        delete(equipmentMenu);
    if (inventoryMenu)
        delete(inventoryMenu);

    if (consoleMenu)
        delete(consoleMenu);
    if (dialogMenu)
        delete(dialogMenu);

    if (itemMenu)
        delete(itemMenu);
    if (characterMenu)
        delete(characterMenu);
    if (spellMenu)
        delete(spellMenu);

    if (tileset)
        SDL_DestroyTexture(tileset);
}