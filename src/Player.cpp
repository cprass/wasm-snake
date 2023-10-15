
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

#include "Player.h"

#include "SDL2/SDL.h"

#include "Globals.h"
#include "Input.h"

namespace snake {

    Player::Player() {
        _head = {14, 14};
        _tail = {
                Rect{14, 15},
                Rect{14, 16},
                Rect{14, 17},
                Rect{14, 18},
                Rect{14, 19},
        };
        _direction = Direction::Up;
    };

    Player::~Player() =default;

    void Player::draw(Graphics &graphics) {
        auto renderer = graphics.getRenderer();
        config::colors::PLAYER.activate(renderer);
        int size = config::TILE_SIZE;
        SDL_Rect rect{
            size * (int)_head.first,
            size * (int)_head.second,
            size,
            size
        };
        SDL_RenderFillRect(renderer, &rect);

        for (auto vec : _tail) {
            vec.draw(graphics);
        }
    }

    void Player::_move() {
        // If tail exists, create a new tail part at the current head position
        if (!_tail.empty()) {
            _tail.insert(_tail.begin(), Rect{
                _head.first,
                _head.second,
            });
            _tail.pop_back();
        }

        // Set new head position
        switch (_direction) {
            case Direction::Up:
                _head.second = std::max((Uint32)0, _head.second - 1);
                break;
            case Direction::Down:
                _head.second = std::min((Uint32)config::BOARD_TILES_VERTICAL, _head.second + 1);
                break;
            case Direction::Left:
                _head.first = std::max((Uint32)0, _head.first - 1);
                break;
            case Direction::Right:
                _head.first = std::min((Uint32)config::BOARD_TILES_HORIZONTAL, _head.first + 1);
                break;
            default:
                break;
        }
    }

    void Player::_parseDirection(Input &input) {
        switch (input.getPressedKey()) {
            case SDL_SCANCODE_UP:
                _setDirection(Direction::Up);
                break;
            case SDL_SCANCODE_DOWN:
                _setDirection(Direction::Down);
                break;
            case SDL_SCANCODE_LEFT:
                _setDirection(Direction::Left);
                break;
            case SDL_SCANCODE_RIGHT:
                _setDirection(Direction::Right);
                break;
            default:
                break;
        }
    }

    void Player::update(double elapsedTimeS, Input &input) {
        _parseDirection(input);
        _move();
    }

    void Player::_setDirection(Direction dir) {
        // TODO: only allow direction that is not moving towards the first tail piece

        _direction = dir;
    }

} // snake