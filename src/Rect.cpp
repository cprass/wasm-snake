
#include "Rect.h"
#include "Globals.h"
#include "SDL2/SDL.h"

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