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
#include "Graphics.h"

namespace snake {

    Graphics::Graphics() {
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();

        SDL_CreateWindowAndRenderer(config::WIDTH , config::HEIGHT, 0, &window, &renderer);
        SDL_SetWindowTitle(window, "wasm-snake");


        // TODO: find a better way to load fonts dynamically
        font = TTF_OpenFont("/home/chris/fonts/snake-wasm/regular.ttf", 32);
        if (font == nullptr) {
            std::cout << "Could not load font: " << TTF_GetError() << std::endl;
            exit(1);
        }
    }

    Graphics::~Graphics() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        TTF_CloseFont(font);

        SDL_Quit();
        TTF_Quit();
    }

    void Graphics::flip() {
        SDL_RenderPresent(renderer);
    }

    void Graphics::clear() {
        config::colors::BACKGROUND.activate(renderer);
        SDL_RenderClear(renderer);
    }

    SDL_Renderer* Graphics::getRenderer() const {
        return renderer;
    }

    SDL_Texture* Graphics::createTextTexture(const std::string& text) {
        SDL_Surface* surfaceText = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceText);
        SDL_FreeSurface(surfaceText);
        return texture;
    }

} // snake
