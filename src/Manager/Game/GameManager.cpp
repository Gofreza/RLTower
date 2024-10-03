#include "GameManager.h"

GameManager::GameManager()
: player(CharactersManager::instance().getPlayer())
{
}

void GameManager::initialize()
{   
    // Initialize the map
    MapManager::instance().generateMap(100, 100, 5);
    MapManager::instance().addPlayer(player);

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

    int player_x = player->getXPosition();  // Integer player position
    int player_y = player->getYPosition();

    // Tile size (assuming 20x20 pixels per tile)
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
                char tile_char = ascii_map[map_y][map_x];
                int ascii_value = static_cast<int>(tile_char);

                SDL_Rect src = tiles[ascii_value];

                // Set destination rect for rendering
                SDL_Rect dest;
                dest.x = x * tile_size;
                dest.y = y * tile_size;
                dest.w = tile_size;
                dest.h = tile_size;

                SDL_RenderCopy(renderer, tileset, &src, &dest);
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
