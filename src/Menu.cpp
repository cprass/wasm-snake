/*
 * Copyright (c) 2023 Christian Praß
 * This file is part of wasm-snake.
 *
 * wasm-snake is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * wasm-snake is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with wasm-snake. If not, see <https://www.gnu.org/licenses/>.
 */

#include "Menu.h"

namespace snake {

    Menu::Menu(Graphics& graphics): isOpen(false) {
        headerTexture = graphics.createTextTexture("Snake    ");
        entryTextures = {
                graphics.createTextTexture("Restart   "),
                graphics.createTextTexture("Exit      ")
        };
    }

    Menu::~Menu() {
        SDL_DestroyTexture(headerTexture);
        for (auto texture : entryTextures) {
            SDL_DestroyTexture(texture);
        }
    };

    bool Menu::getIsOpen() {
        return isOpen;
    }

    void Menu::update(double elapsedTimeS, Input &input) {
        switch (input.getPressedKey()) {
            case SDL_SCANCODE_ESCAPE:
                isOpen = true;
                break;
            default:
                break;
        }
    }

    void Menu::draw(Graphics &graphics) {
        SDL_Renderer* renderer = graphics.getRenderer();

        int menuItemHeight = 50;
        int menuItemWidth = 250;

        int x = 165;
        int y = 100;

        SDL_Rect bg{ 20, 20, 540, 540};

        config::colors::BACKGROUND.activate(renderer);
        SDL_RenderFillRect(renderer, &bg);

        config::colors::BORDER.activate(renderer);
        SDL_RenderDrawRect(renderer, &bg);

        config::colors::FONT.activate(renderer);

        SDL_Rect hRect{ x, y, menuItemWidth, menuItemHeight};
        SDL_RenderCopy(renderer, headerTexture, NULL, &hRect);

        for (int i = 0; i < size(entryTextures); i++) {
            SDL_Rect rect{ x, y + (i + 3) * menuItemHeight, menuItemWidth, menuItemHeight};
            SDL_RenderCopy(renderer, entryTextures.at(i), NULL, &rect);
        }

    }

} // snake