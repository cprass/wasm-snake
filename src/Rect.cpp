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

#include "Rect.h"

namespace snake {

    Rect::Rect(unsigned int x, unsigned int y) {
        int size = config::TILE_SIZE;
        _rect = SDL_Rect{
            size * (int)x,
            size * (int)y,
            size,
            size
        };
    };

    Rect::~Rect() =default;

    void Rect::draw(Graphics &graphics) {
        auto renderer = graphics.getRenderer();
        SDL_RenderFillRect(renderer, &_rect);
    };

} // snake