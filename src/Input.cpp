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

#include "Input.h"

namespace snake {

    // reset the keys that are no longer relevant
    void Input::beingNewFrame() {
        _pressedKey = SDL_SCANCODE_UNKNOWN;
    }

    void Input::keyDownEvent(const SDL_Event &event) {
        _pressedKey = event.key.keysym.scancode;
    }

    SDL_Scancode Input::getPressedKey() {
        return _pressedKey;
    }

} // snake