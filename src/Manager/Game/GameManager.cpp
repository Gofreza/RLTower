#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::initialize()
{   
    // Initialize the map
    MapManager::instance().generateMap(100, 100, 5);
    MapManager::instance().addPlayer();

    std::cout << "Map generated" << std::endl;
    // MapManager::instance().printDungeonMap();
}

void GameManager::update()
{
}

void GameManager::renderMap(SDL_Renderer* renderer, const SDL_Rect& rect, SDL_Texture* tileset, const std::vector<SDL_Rect>& tiles)
{
    const auto& ascii_map = MapManager::instance().getAsciiMap();
    const int map_width = ascii_map[0].size();
    const int map_height = ascii_map.size();

    Player* player = CharactersManager::instance().getPlayer();
    int player_x = player->getXPosition();
    int player_y = player->getYPosition();

    // Render the map with the player in the center
    int half_width = rect.w / 2;
    int half_height = rect.h / 2;

    int start_x = player_x - half_width / 20;
    int start_y = player_y - half_height / 20;

    for (int y = 0; y < rect.h / 20; y++) {
        for (int x = 0; x < rect.w / 20; x++) {
            int map_x = start_x + x;
            int map_y = start_y + y;

            if (map_x >= 0 && map_x < map_width && map_y >= 0 && map_y < map_height) {
                char tile_char = ascii_map[map_y][map_x];
                int ascii_value = (int)tile_char;

                SDL_Rect src = tiles[ascii_value];

                SDL_Rect dest;
                dest.x = x * 20;
                dest.y = y * 20;
                dest.w = 20;
                dest.h = 20;

                SDL_RenderCopy(renderer, tileset, &src, &dest);
            }
        }
    }
}

GameManager::~GameManager()
{
}
