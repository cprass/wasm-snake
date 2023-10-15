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
#ifndef WASM_SNAKE_GRAPHICS_H
#define WASM_SNAKE_GRAPHICS_H

#include "SDL2/SDL.h"

namespace snake {

    class Graphics {
    public:
        Graphics();
        ~Graphics();

        void flip();
        void clear();
        SDL_Renderer* getRenderer() const;

    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;
    };

} // snake

#endif //WASM_SNAKE_GRAPHICS_H
