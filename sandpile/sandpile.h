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

struct Sandpile {
    uint64_t unstables = 0;
    Vector<Vector<Pixel>> matrix;

    bool is_stable() {
        return unstables == 0;
    }

    void add_unstables(size_t i, size_t j) {
        if (matrix[i][j].piles == 4) {
            ++unstables;
        }
    }
};

bool Collapse(Sandpile& sandpile, size_t i, size_t j);

#include "../image/image.h"
#include "../parser/parser.h"
void Shake(Sandpile& sandpile, const Args& args);
