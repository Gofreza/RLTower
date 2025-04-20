#include "ConsoleMenu.h"
#include "../Misc/Utils.h"
#include "../Misc/Logger.h"

#include "../Manager/Localization/LocalizationManager.h"
#include "../Manager/UI/UiManager.h"

ConsoleMenu::ConsoleMenu (SDL_Renderer* renderer, TTF_Font* font)
: Menu(renderer, font)
{
    std::string headerText = LocalizationManager::instance().getText("logs_title");
    headerTextTexture = Utils::loadTextTexture(renderer, font, headerText, Utils::textColor);
}

void ConsoleMenu::render(const SDL_Rect& rect) {

    int textWidth = 0, textHeight = 0;
    if (headerTextTexture) {
        SDL_QueryTexture(headerTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect headerRect = {
            (rect.w - textWidth) / 2, 
            rect.y + 5, 
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer, headerTextTexture, nullptr, &headerRect);
    }

    SDL_Rect logsRect = {
        rect.x,
        rect.y + textHeight + 5 + 5,
        rect.w,
        rect.h - textHeight - 5 - 5
    };
    
    UiManager::instance().drawBorder(renderer, logsRect, Utils::borderColor);
    
    // Start rendering from the bottom of logsRect
    // int currentY = logsRect.y + logsRect.h - 5;

    // // Get the log messages
    // auto* logMessages = Logger::instance().getLogMessages();

    // for (auto it = logMessages->rbegin(); it != logMessages->rend(); ++it) {
    //     SDL_Texture* messageTexture = Utils::loadTextTexture(renderer, font, *it, Utils::textColor);
    //     if (messageTexture) {
    //         int messageWidth = 0, messageHeight = 0;
    //         SDL_QueryTexture(messageTexture, nullptr, nullptr, &messageWidth, &messageHeight);
    //         currentY -= (messageHeight + 5); // Move up by the height of the text and some padding

    //         // If the message is out of the visible area, stop rendering
    //         if (currentY < logsRect.y) {
    //             SDL_DestroyTexture(messageTexture);
    //             it = decltype(it){logMessages->erase(std::next(it).base())};
    //             break;
    //         }

    //         SDL_Rect messageRect = {
    //             logsRect.x + 5, 
    //             currentY,
    //             messageWidth,
    //             messageHeight
    //         };
    //         SDL_RenderCopy(renderer, messageTexture, nullptr, &messageRect);
    //         SDL_DestroyTexture(messageTexture); 
    //     }
    // }

    // Start rendering from the bottom of logsRect
    int currentY = logsRect.y + logsRect.h - 5;
    int maxWidth = logsRect.w - 10;

    auto* logMessages = Logger::instance().getLogMessages();

    for (auto it = logMessages->rbegin(); it != logMessages->rend(); ) {
        std::vector<std::string> wrappedLines;
        std::string currentLine;
        std::istringstream words(*it);
        std::string word;
        int spaceWidth, textWidth, textHeight;

        TTF_SizeText(font, " ", &spaceWidth, nullptr);

        while (words >> word) {
            std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
            TTF_SizeText(font, testLine.c_str(), &textWidth, &textHeight);

            if (textWidth > maxWidth) {
                if (!currentLine.empty()) {
                    wrappedLines.push_back(currentLine);
                }
                currentLine = word;
            } else {
                currentLine = testLine;
            }
        }
        if (!currentLine.empty()) {
            wrappedLines.push_back(currentLine);
        }

        bool fitsOnScreen = false;

        for (auto lineIt = wrappedLines.rbegin(); lineIt != wrappedLines.rend(); ++lineIt) {
            SDL_Texture* messageTexture = Utils::loadTextTexture(renderer, font, *lineIt, Utils::textColor);
            if (messageTexture) {
                SDL_QueryTexture(messageTexture, nullptr, nullptr, &textWidth, &textHeight);

                if (currentY - textHeight < logsRect.y) {
                    SDL_DestroyTexture(messageTexture);
                    break;  // Stop rendering this message's lines
                }

                currentY -= (textHeight + 5);
                fitsOnScreen = true;

                SDL_Rect messageRect = {
                    logsRect.x + 5,
                    currentY,
                    textWidth,
                    textHeight
                };
                SDL_RenderCopy(renderer, messageTexture, nullptr, &messageRect);
                SDL_DestroyTexture(messageTexture);
            }
        }

        if (!fitsOnScreen) {
            // Message doesn't fit at all -> erase it
            it = decltype(it){logMessages->erase(std::next(it).base())};
            // Do NOT break! Keep checking older messages
        } else {
            ++it; // Message was at least partially rendered
        }

        // Stop rendering older messages if there's no more vertical space
        if (currentY < logsRect.y) {
            break;
        }
    }

}

int ConsoleMenu::getHeight() const {
    return -1;
} 

ConsoleMenu::~ConsoleMenu ()
{
    SDL_DestroyTexture(headerTextTexture);
}