#include <sstream>
#include "DialogMenu.h"
#include "../Misc/Utils.h"

#include "../Manager/Localization/LocalizationManager.h"

DialogMenu::DialogMenu (SDL_Renderer* renderer, TTF_Font* font)
: Menu(renderer, font)
{
    std::string headerText = LocalizationManager::instance().getText("dialog_title");
    headerTextTexture = Utils::loadTextTexture(renderer, font, headerText, Utils::textColor);
}

void DialogMenu::render(const SDL_Rect& rect) {

    int textWidth = 0, textHeight = 0;
    if (headerTextTexture) {
        SDL_QueryTexture(headerTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect headerRect = {
            rect.x + (rect.w - textWidth) / 2, 
            rect.y + 5, 
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer, headerTextTexture, nullptr, &headerRect);
    }

    SDL_Rect dialogRect = {
        rect.x,
        rect.y + textHeight + 5 + 5,
        rect.w,
        rect.h - textHeight - 5 - 5
    };

    currentY = rect.y + textHeight + 5 + 5;
    
    drawBorder(renderer, dialogRect, Utils::borderColor);
}

void DialogMenu::render(const SDL_Rect& rect, const Item* item) {
    render(rect);
    // Render the item
    int textWidth = 0, textHeight = 0;
    currentY += 5;
    int descriptionY = currentY;

    // Image
    std::string imagePath = Utils::getImagePath(item->getImagePath());
    SDL_Surface* imgSurface = IMG_Load(imagePath.c_str());
    float ratio = static_cast<float>((rect.h - 4) / 2 - 10) / imgSurface->h;
    int imgWidth = imgSurface->w * ratio;
    SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);
    SDL_FreeSurface(imgSurface);
    SDL_Rect imgRect = {
        rect.x + 5,
        currentY,
        imgWidth,
        (rect.h - 4) / 2 - 10
    };
    SDL_RenderCopy(renderer, imgTexture, nullptr, &imgRect);
    SDL_DestroyTexture(imgTexture);
    descriptionY += (rect.h - 4) / 2 - 10 + 5;

    // Name
    SDL_Texture* itemNameTextTexture = Utils::loadTextTexture(renderer, font, item->getName(), Utils::textColor);
    if (itemNameTextTexture) {
        SDL_QueryTexture(itemNameTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect itemNameRect = {
            rect.x + 5 + imgWidth + 5,
            currentY,
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer, itemNameTextTexture, nullptr, &itemNameRect);
        SDL_DestroyTexture(itemNameTextTexture);
        currentY += textHeight + 5;
    }
    SDL_DestroyTexture(itemNameTextTexture);

    // Type
    std::string typeText = LocalizationManager::instance().getText("item_type") + to_string(item->getType());
    SDL_Texture* typeTextTexture = Utils::loadTextTexture(renderer, font, typeText, Utils::textColor);
    if (typeTextTexture) {
        SDL_QueryTexture(typeTextTexture, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect typeRect = {
            rect.x + 5 + imgWidth + 5, 
            currentY, 
            textWidth,
            textHeight
        };
        currentY += textHeight + 5;
        SDL_RenderCopy(renderer, typeTextTexture, nullptr, &typeRect);
    }
    SDL_DestroyTexture(typeTextTexture);

    // Rarity
    std::string rarityLabel = LocalizationManager::instance().getText("item_rarity");
    SDL_Texture* rarityLabelTexture = Utils::loadTextTexture(renderer, font, rarityLabel, Utils::textColor);
    if (rarityLabelTexture) {
        int labelWidth = 0, labelHeight = 0;
        SDL_QueryTexture(rarityLabelTexture, nullptr, nullptr, &labelWidth, &labelHeight);
        SDL_Rect labelRect = {
            rect.x + 5 + imgWidth + 5, 
            currentY, 
            labelWidth,
            labelHeight
        };
        SDL_RenderCopy(renderer, rarityLabelTexture, nullptr, &labelRect);
        SDL_DestroyTexture(rarityLabelTexture);

        // Render rarity value
        std::string rarityValue = to_string(item->getRarity());
        SDL_Color valueColor = getRarityColor(item->getRarity());
        SDL_Texture* rarityValueTexture = Utils::loadTextTexture(renderer, font, rarityValue, valueColor);

        if (rarityValueTexture) {
            int valueWidth = 0, valueHeight = 0;
            SDL_QueryTexture(rarityValueTexture, nullptr, nullptr, &valueWidth, &valueHeight);
            SDL_Rect valueRect = {
                rect.x + labelWidth + 5 + imgWidth + 5, 
                currentY, 
                valueWidth,
                valueHeight
            };
            SDL_RenderCopy(renderer, rarityValueTexture, nullptr, &valueRect);
            SDL_DestroyTexture(rarityValueTexture);
        }

        currentY += labelHeight + 5; // Update currentY for the next item to render
    }

    // Description
    std::string descriptionText = LocalizationManager::instance().getText("item_description") + item->getDescription();
    std::vector<std::string> lines;
    std::string currentLine;
    std::istringstream words(descriptionText);
    std::string word;
    int maxWidth = rect.w - 10;  // Adjust for padding
    int spaceWidth;

    // Measure the width of a space character (you can assume spaceWidth as needed)
    TTF_SizeText(font, " ", &spaceWidth, nullptr);

    while (words >> word) {
        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
        TTF_SizeText(font, testLine.c_str(), &textWidth, &textHeight);

        if (textWidth > maxWidth) {
            // Current word does not fit on the current line, push the current line and start a new one
            lines.push_back(currentLine);
            currentLine = word;  // Start the new line with the current word
        } else {
            // Word fits on the current line
            currentLine = testLine;
        }
    }

    // Don't forget to add the last line
    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    // Now render each line
    for (const std::string& line : lines) {
        SDL_Texture* descriptionTextTexture = Utils::loadTextTexture(renderer, font, line, Utils::textColor);
        if (descriptionTextTexture) {
            SDL_QueryTexture(descriptionTextTexture, nullptr, nullptr, &textWidth, &textHeight);
            SDL_Rect descriptionRect = {
                rect.x + 5, 
                descriptionY, 
                textWidth,
                textHeight
            };
            SDL_RenderCopy(renderer, descriptionTextTexture, nullptr, &descriptionRect);
            SDL_DestroyTexture(descriptionTextTexture);

            // Move to the next line
            currentY += textHeight + 5;
        }
    }
}

void DialogMenu::render(const SDL_Rect& rect, const Character* character) {
    render(rect);
    // Render the character
}

int DialogMenu::getHeight() const {
    return -1;
} 

DialogMenu::~DialogMenu ()
{
    SDL_DestroyTexture(headerTextTexture);
}