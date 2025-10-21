#include "DebugMenu.h"
#include "../../Manager/Game/GameManager.h"

DebugMenu::DebugMenu(SDL_Renderer* renderer, TTF_Font* font)
: Menu(renderer, font),
selectedCharacter(nullptr), isFovEnabled(false)
{
}

void DebugMenu::render(const SDL_Rect& rect) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Get enemies
    std::vector<Enemy*>& enemies = GameManager::instance().getEnemies();
    int currentY = rect.y + 5;

    const int padding = 5;
    for (Enemy* enemy : enemies) {
        if (!enemy) continue;

        SDL_Texture* enemyNameTextTexture = Utils::loadTextTexture(renderer, font, enemy->getName(), Utils::textColor);
        int textWidth = 0, textHeight = 0;
        SDL_QueryTexture(enemyNameTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        int singleEnemyMenuHeight = textHeight + 2 * padding;
        SDL_Rect enemyNameRect = {
            rect.x + padding * 2,
            currentY + padding,
            textWidth,
            textHeight
        };
        SDL_Rect enemyMenuRect = {
            rect.x + 5,
            currentY,
            rect.w - padding * 2,
            singleEnemyMenuHeight
        };

        if (isMouseHovering(enemyMenuRect, 0)) {
            SDL_SetRenderDrawColor(renderer, Utils::hoverBackColor.r, Utils::hoverBackColor.g, Utils::hoverBackColor.b, 255);
            SDL_RenderFillRect(renderer, &enemyMenuRect);
        }

        Menu::drawBorder(renderer, enemyMenuRect, Utils::borderColor, 1);
        SDL_RenderCopy(renderer, enemyNameTextTexture, nullptr, &enemyNameRect);
        SDL_DestroyTexture(enemyNameTextTexture);
        currentY += singleEnemyMenuHeight + padding;

        if (InputManager::instance().isLeftClicked() && isMouseHovering(enemyMenuRect, 0)) {
            InputManager::instance().deactivateLeftClick();
            if (selectedCharacter == enemy) {
                // MapManager::instance().hightlightEnemyFov(selectedCharacter, true, enemy->getXPosition(), enemy->getYPosition());
                MapManager::instance().highlightEnemy(selectedCharacter, true);
                isFovEnabled = false;
                selectedCharacter = nullptr;
            } else {
                if (selectedCharacter) {
                    // MapManager::instance().hightlightEnemyFov(selectedCharacter, true, selectedCharacter->getXPosition(), selectedCharacter->getYPosition());
                    MapManager::instance().highlightEnemy(selectedCharacter, true);
                    isFovEnabled = false;
                }
                // MapManager::instance().hightlightEnemyFov(enemy);
                MapManager::instance().highlightEnemy(enemy);
                selectedCharacter = enemy;
                isFovEnabled = true;
            }
        }

        // if (selectedCharacter && isFovEnabled) {
        //     std::vector<Cell*>& lastVisitedCells = selectedCharacter->getLastVisitedCells();
        //     if (lastVisitedCells.size() > 0) {
        //         MapManager::instance().hightlightEnemyFov(selectedCharacter, true, lastVisitedCells.at(0)->getX(), lastVisitedCells.at(0)->getY());
        //     }
        //     MapManager::instance().hightlightEnemyFov(selectedCharacter);
        // }
    }

    // Draw a line
    SDL_SetRenderDrawColor(renderer, Utils::borderColor.r, Utils::borderColor.g, Utils::borderColor.b, 255);
    SDL_RenderDrawLine(renderer, rect.x + 5, currentY, rect.x + rect.w - 5, currentY);
    currentY += 5;

    // Draw data about the selected enemy
    if (selectedCharacter) {
        // Draw direction
        AICells aiCells = selectedCharacter->getAICells();

        int northValue = aiCells.nortValue;
        renderWithoutColor(rect, currentY, "North:", std::to_string(northValue));
        int southValue = aiCells.southValue;
        renderWithoutColor(rect, currentY, "South:", std::to_string(southValue));
        int eastValue = aiCells.eastValue;
        renderWithoutColor(rect, currentY, "East:", std::to_string(eastValue));
        int westValue = aiCells.westValue;
        renderWithoutColor(rect, currentY, "West:", std::to_string(westValue));

        // Draw a line
        SDL_SetRenderDrawColor(renderer, Utils::borderColor.r, Utils::borderColor.g, Utils::borderColor.b, 255);
        SDL_RenderDrawLine(renderer, rect.x + 5, currentY, rect.x + rect.w - 5, currentY);
        currentY += 5;

        // Draw AIDecision
        AIDecision decision = aiCells.decision;
        renderWithoutColor(rect, currentY, "Aggression:", std::to_string(decision.aggression));
        renderWithoutColor(rect, currentY, "Fear:", std::to_string(decision.fear));
        renderWithoutColor(rect, currentY, "Desire:", std::to_string(decision.desire));
        renderWithoutColor(rect, currentY, "Wander:", std::to_string(decision.wander));
        renderWithoutColor(rect, currentY, "Misc:", std::to_string(decision.misc));
        renderWithoutColor(rect, currentY, "Blocked:", decision.blocked ? "true" : "false");
        renderWithoutColor(rect, currentY, "Action:", actionTypeToString(selectedCharacter->getActionType()));
        renderWithoutColor(rect, currentY, "Is in Combat:", selectedCharacter->isCharacterInCombat() ? "true" : "false");
    }
    
}

void DebugMenu::renderWithoutColor(const SDL_Rect& rect, int& currentY, std::string label, std::string value) {
    int textWidth = 0, textHeight = 0;
    std::string text = label + value;
    SDL_Texture* textTexture = Utils::loadTextTexture(renderer, font, text, Utils::textColor);
    if (textTexture) {
        SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect durabilityRect = {
            rect.x + 5, 
            currentY, 
            textWidth,
            textHeight
        };
        currentY += textHeight + 5;
        SDL_RenderCopy(renderer, textTexture, nullptr, &durabilityRect);
    }
    SDL_DestroyTexture(textTexture);
}

int DebugMenu::getHeight() const {
    return -1;
} 

DebugMenu::~DebugMenu ()
{
}