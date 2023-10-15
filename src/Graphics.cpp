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
#include "Globals.h"

namespace snake {

    Graphics::Graphics() {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_CreateWindowAndRenderer(config::WIDTH , config::HEIGHT, 0, &window, &renderer);
        SDL_SetWindowTitle(window, "wasm-snake");

        _window = window;
        _renderer = renderer;
    }

    Graphics::~Graphics() {
        SDL_DestroyWindow(_window);
        SDL_DestroyRenderer(_renderer);
    }

    void Graphics::flip() {
        SDL_RenderPresent(_renderer);
    }

    void Graphics::clear() {
        config::colors::BACKGROUND.activate(_renderer);
        SDL_RenderClear(_renderer);
    }

    SDL_Renderer* Graphics::getRenderer() const {
        return _renderer;
    }



} // snake
