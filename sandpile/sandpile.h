#pragma once
#include <cstdint>

struct Pixel {
    int64_t x = 0;
    int64_t y = 0;
    uint64_t piles = 0;
    
    Pixel(int64_t _x, int64_t _y, uint64_t _piles) {
        x = _x;
        y = _y;
        piles = _piles;
    }

    Pixel() = default;
};