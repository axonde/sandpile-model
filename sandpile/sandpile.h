#pragma once
#include <cstdint>

struct Pixel {
    uint64_t piles = 0;
    
    Pixel(uint64_t _piles) {
        piles = _piles;
    }

    Pixel() = default;
};