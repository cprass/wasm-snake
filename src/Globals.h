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

#ifndef WASM_SNAKE_GLOBALS_H
#define WASM_SNAKE_GLOBALS_H

#include "SDL2/SDL.h"

namespace snake {
    namespace config {
        const int TILE_SIZE = 20;
        const int BOARD_TILES_HORIZONTAL = 29;
        const int BOARD_TILES_VERTICAL = 29;
        const int WIDTH = TILE_SIZE * BOARD_TILES_HORIZONTAL;
        const int HEIGHT = TILE_SIZE * BOARD_TILES_VERTICAL;

        namespace colors {

            class Color {
            public:
                Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
                void activate(SDL_Renderer *renderer) const;
            private:
                Uint8 r, g, b, a;
            };

            const Color BACKGROUND(0,0,0,SDL_ALPHA_OPAQUE);
            const Color PLAYER(0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
            const Color ENVIRONMENT(0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
        }
    }

    enum Direction {
        Up,
        Down,
        Left,
        Right,
    };
}

#endif //WASM_SNAKE_GLOBALS_H
