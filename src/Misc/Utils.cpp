#include "Utils.h"
#include <filesystem>

namespace Utils {
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
        SDL_Texture* texture = nullptr;
        if (renderer == nullptr) {
            std::cerr << "Renderer is null!" << std::endl;
            return texture;
        }

        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == nullptr) {
            std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        } else {
            texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            if (texture == nullptr) {
                std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
            }
            SDL_FreeSurface(loadedSurface);
        }
        return texture;
    }

    bool initSDL_TTF(TTF_Font*& font, const std::string& fontPath, int fontSize) {
        if (TTF_Init() == -1) {
            std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
            return false;
        }

        font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!font) {
            std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
            return false;
        }
        return true;
    }

    /**
     * Create a texture with the given text
     * 
     * - Don't forget to Destroy the previous texture if you're re-assigning
     * a new texture to an already existing variable with a texture.
     */
    SDL_Texture* loadTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (!textSurface) {
            std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
            return nullptr;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
        if (!textTexture) {
            std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        }
        return textTexture;
    }

    /**
     * Get the current working directory of the application
     */
    std::string getCWD() {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            std::cout << "Current working directory: " << cwd << std::endl;
        }
        return std::string(cwd);
    }

    /**
     * Get the full path of an image
     */
    // TODO: Change path when packaging the game
    std::string getImagePath(const std::string& imageName) {
        std::string cwd = std::filesystem::canonical(std::filesystem::current_path()).string();
        std::string imagePath = cwd + "/../res/images/" + imageName;
        return imagePath;
    }

    /**
     * Check if the mouse is hovering over a rect
     */
    bool isMouseHovering(const SDL_Rect& rect, int renderTargetX, int renderTargetY) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Adjust the mouse position relative to the render target
        int adjustedX = mouseX - renderTargetX;
        int adjustedY = mouseY - renderTargetY;

        // Check if the adjusted mouse position is within the rect
        return (adjustedX >= rect.x && adjustedX < rect.x + rect.w &&
                adjustedY >= rect.y && adjustedY < rect.y + rect.h);
    }

    /**
     * Calculate the distance between two points
     */
    float distance(int x1, int y1, int x2, int y2) {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    SDL_Color borderColor = {255, 255, 255, 255}; // White border
    SDL_Color textColor = {255, 255, 255, 255};  // White text
    SDL_Color hoverColor = {215, 215, 215, 255}; // Grey text
    SDL_Color hoverBackColor = {120, 120, 120, 255}; // Grey text
    SDL_Color hpBarBorderColor = {255, 255, 255, 255}; // White HP bar border
    SDL_Color hpFillColor = {255, 0, 0, 255};    // Red for HP fill
    SDL_Color manaBarBorderColor = {255, 255, 255, 255}; // White Mana bar border
    SDL_Color manaFillColor = {0, 0, 255, 255};    // Blue for Mana fill
    SDL_Color energyBarBorderColor = {255, 255, 255, 255}; // White Energy bar border
    SDL_Color energyFillColor = {255, 195, 0, 255};    // Yellow for Energy fill
    SDL_Color staminaBarBorderColor = {255, 255, 255, 255}; // White border
    SDL_Color staminaFillColor = {50, 200, 50, 255}; // Green

    SDL_Color phyCombatColor = {255, 0, 0, 255}; // Red
    SDL_Color magCombatColor = {0, 0, 255, 255}; // Blue
}
