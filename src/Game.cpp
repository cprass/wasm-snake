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

namespace snake {

    const Uint64 FPS = 10;
    const Uint64 TARGET_FRAME_TIME_MS = 1000 / FPS;
    const Uint64 MAX_FRAME_TIME_MS = 5000;

    Game::Game(): input(), graphics(), player(), level(), menu(Menu(graphics)) {
        gameLoop();
    }

    Game::~Game() =default;

    void Game::gameLoop() {
        SDL_Event e;
        bool quit = false;

        Uint64 lastUpdateTimeMS = SDL_GetTicks64();

        while (!quit) {
            input.beingNewFrame();

            while (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_KEYDOWN:
                        if (e.key.repeat == 0) {
                            input.keyDownEvent(e);
                        }
                        break;
                    case SDL_QUIT:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }

            switch (input.getPressedKey()) {
                case SDL_SCANCODE_ESCAPE:
                    if (!isMenuOpen) {
                        isMenuOpen = true;
                    } else if (!isGameOver) {
                        isMenuOpen = false;
                    }
                default:
                    break;
            }

            Uint64 elapsedTimeMS = SDL_GetTicks64() - lastUpdateTimeMS;
            lastUpdateTimeMS = SDL_GetTicks64();

            update((double)std::min(elapsedTimeMS, MAX_FRAME_TIME_MS) / 1000.0);
            checkCollisions();
            draw();

            Uint64 currFrameElapsedTime = SDL_GetTicks64() - lastUpdateTimeMS;
            auto remainingTime = std::max((Uint64)0, TARGET_FRAME_TIME_MS - currFrameElapsedTime);

            if (remainingTime > 0) {
                SDL_Delay(remainingTime);
            }
        }
    }

    void Game::draw() {
        graphics.clear();

        level.draw(graphics);
        player.draw(graphics);

        if (isMenuOpen) {
            menu.draw(graphics);
        }

        graphics.flip();
    }

    void Game::update(double elapsedTimeS) {
        if (isMenuOpen) {
            menu.update(elapsedTimeS, input);
        } else {
            // update player and level only if the menu is not currently opened
            player.update(elapsedTimeS, input);
            // TODO: update level
        }
    }

    void Game::checkCollisions() {

    }

} // snake
