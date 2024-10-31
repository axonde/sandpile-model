#pragma once
#include <cstdint>
#include <cstddef>
#include "../vector/vector.h"

struct Pixel {
    uint64_t piles = 0;
    
    Pixel(uint64_t _piles) {
        piles = _piles;
    }

    Pixel() = default;
};

void Collapse(Vector<Vector<Pixel>>& matrix, size_t x, size_t y);