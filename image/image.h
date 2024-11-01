#pragma once
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include "../sandpile/sandpile.h"
#include "../vector/vector.h"

struct Color {
    uint8_t r = 0, g = 0, b = 0;

    Color() = default;
    Color(float _r, float _g, float _b);
};

void Export(const Vector<Vector<Pixel>>& matrix, const std::string& _path, const std::string& filename);
uint8_t GetColorIndex(const Vector<Vector<Pixel>>& matrix, uint64_t x, uint64_t y);
