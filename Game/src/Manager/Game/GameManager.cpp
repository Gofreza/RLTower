#include "GameManager.h"
#include "../../Misc/Utils.h"

GameManager::GameManager()
: player(CharactersManager::instance().getPlayer())
{
}

void GameManager::initialize()
{   
    // Initialize the map
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
    movePlayer();
}

void GameManager::renderMap(SDL_Renderer* renderer, const SDL_Rect& rect, SDL_Texture* tileset, const std::vector<SDL_Rect>& tiles)
{
    const auto& ascii_map = MapManager::instance().getAsciiMap();
    const int map_width = ascii_map[0].size();
    const int map_height = ascii_map.size();

    int player_x = player->getXPosition(); 
    int player_y = player->getYPosition();

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

                if (!ascii_map[map_y][map_x].isExplored) {
                    // Render a dark cell
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &dest);
                } else {
                    char tile_char = ascii_map[map_y][map_x].getSymbol();
                    int ascii_value = static_cast<int>(tile_char);

                    src = tiles[ascii_value];

                    if (ascii_map[map_y][map_x].isInSight) {
                        // Change the color of the src
                        SDL_SetTextureColorMod(tileset, ascii_map[map_y][map_x].currentColor.r, ascii_map[map_y][map_x].currentColor.g, ascii_map[map_y][map_x].currentColor.b); 
                        // Set background color to light gray
                        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
                    } else {
                        // Change the color of the src
                        SDL_SetTextureColorMod(tileset, 100, 100, 100);
                        // Set background color to default
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    }

                    // Render the background
                    SDL_RenderFillRect(renderer, &dest);
                    // Render the tile
                    SDL_RenderCopy(renderer, tileset, &src, &dest);
                } 

                // Listeners
                // TODO: Check if the mouse is inside the rect, if not doesn't render the hover effect
                if (Utils::isMouseHovering(dest, rect.x, rect.y)) {
                    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
                    SDL_RenderFillRect(renderer, &dest);
                    SDL_RenderCopy(renderer, tileset, &src, &dest);
                }    
            }
        }
    }
}

void GameManager::movePlayer() {
    bool moved = false;
    if (InputManager::instance().isKeyPressed(SDLK_UP)) {
        InputManager::instance().deactivateKey(SDLK_UP);

        if (MapManager::instance().canPlayerMove(player, 0, -1)) {
            player->move(0, -1);
            MapManager::instance().movePlayerInMap(player, 0, -1);  
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(SDLK_DOWN)) {
        InputManager::instance().deactivateKey(SDLK_DOWN);

        if (MapManager::instance().canPlayerMove(player, 0, 1)) {
            player->move(0, 1);
            MapManager::instance().movePlayerInMap(player, 0, 1);
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(SDLK_LEFT)) {
        InputManager::instance().deactivateKey(SDLK_LEFT);

        if (MapManager::instance().canPlayerMove(player, -1, 0)) {
            player->move(-1, 0);
            MapManager::instance().movePlayerInMap(player, -1, 0);
            moved = true;
        }
    }
    if (InputManager::instance().isKeyPressed(SDLK_RIGHT)) {
        InputManager::instance().deactivateKey(SDLK_RIGHT);

        if (MapManager::instance().canPlayerMove(player, 1, 0)) {
            player->move(1, 0);
            MapManager::instance().movePlayerInMap(player, 1, 0);
            moved = true;
        }
    }
    if (moved) {
        UiManager::instance().updateGame(true);
    }
}

GameManager::~GameManager()
{
}
