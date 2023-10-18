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

namespace snake {

    Player::Player() {
        head = {14, 14};
        tail = {
                Rect{14, 15},
                Rect{14, 16},
                Rect{14, 17},
                Rect{14, 18},
                Rect{14, 19},
        };
        direction = Direction::Up;
    };

    Player::~Player() =default;

    void Player::draw(Graphics &graphics) {
        auto renderer = graphics.getRenderer();
        config::colors::PLAYER.activate(renderer);
        int size = config::TILE_SIZE;
        SDL_Rect rect{
            size * (int)head.first,
            size * (int)head.second,
            size,
            size
        };
        SDL_RenderFillRect(renderer, &rect);

        for (auto vec : tail) {
            vec.draw(graphics);
        }
    }

    void Player::move() {
        // If tail exists, create a new tail part at the current head position
        if (!tail.empty()) {
            tail.insert(tail.begin(), Rect{
                head.first,
                head.second,
            });
            tail.pop_back();
        }

        // Set new head position
        switch (direction) {
            case Direction::Up:
                head.second = std::max((Uint32)0, head.second - 1);
                break;
            case Direction::Down:
                head.second = std::min((Uint32)config::BOARD_TILES_VERTICAL, head.second + 1);
                break;
            case Direction::Left:
                head.first = std::max((Uint32)0, head.first - 1);
                break;
            case Direction::Right:
                head.first = std::min((Uint32)config::BOARD_TILES_HORIZONTAL, head.first + 1);
                break;
            default:
                break;
        }
    }

    void Player::parseDirection(Input &input) {
        switch (input.getPressedKey()) {
            case SDL_SCANCODE_UP:
                setDirection(Direction::Up);
                break;
            case SDL_SCANCODE_DOWN:
                setDirection(Direction::Down);
                break;
            case SDL_SCANCODE_LEFT:
                setDirection(Direction::Left);
                break;
            case SDL_SCANCODE_RIGHT:
                setDirection(Direction::Right);
                break;
            default:
                break;
        }
    }

    void Player::update(double elapsedTimeS, Input &input) {
        parseDirection(input);
        // Player always moves on each update
        move();
    }

    void Player::setDirection(Direction dir) {
        // Simply ignore the movement if it is the opposite of the current direction
        if (dir == Direction::Up && direction == Direction::Down) {
            return;
        }
        if (dir == Direction::Down && direction == Direction::Up) {
            return;
        }
        if (dir == Direction::Left && direction == Direction::Right) {
            return;
        }
        if (dir == Direction::Right && direction == Direction::Left) {
            return;
        }

        direction = dir;
    }

} // snake