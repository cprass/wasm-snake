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

/*
 * Game Class
 * This class holds all information for main game loop
 */

#include "Game.h"
#include "Graphics.h"
#include "Input.h"

namespace snake {

    const Uint64 FPS = 10;
    const Uint64 TARGET_FRAME_TIME_MS = 1000 / FPS;
    const Uint64 MAX_FRAME_TIME_MS = 5000;

    Game::Game(): _input(), _graphics(), _player(), _level() {
        SDL_Init(SDL_INIT_EVERYTHING);
        gameLoop();
    }

    Game::~Game() {
        SDL_Quit();
    }

    void Game::gameLoop() {
        SDL_Event e;
        bool quit = false;

        Uint64 lastUpdateTimeMS = SDL_GetTicks64();

        while (!quit) {
            _input.beingNewFrame();

            while (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_KEYDOWN:
                        if (e.key.repeat == 0) {
                            _input.keyDownEvent(e);
                        }
                        break;
                    case SDL_QUIT:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }

            if (_input.getPressedKey() == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }

            Uint64 elapsedTimeMS = SDL_GetTicks64() - lastUpdateTimeMS;

            update((double)std::min(elapsedTimeMS, MAX_FRAME_TIME_MS) / 1000.0);
            draw();

            elapsedTimeMS = SDL_GetTicks64() - lastUpdateTimeMS;
            auto remainingTime = std::max((Uint64)0, TARGET_FRAME_TIME_MS - elapsedTimeMS);

            if (remainingTime > 0) {
                SDL_Delay(remainingTime);
            }
            lastUpdateTimeMS = SDL_GetTicks64();
        }
    }

    void Game::draw() {
        _graphics.clear();

        _level.draw(_graphics);
        _player.draw(_graphics);

        _graphics.flip();
    }

    void Game::update(double elapsedTimeS) {
        _player.update(elapsedTimeS, _input);
    }

} // snake
