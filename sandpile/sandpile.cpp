#include "sandpile.h"

void Collapse(Vector<Vector<Pixel>>& matrix, size_t i, size_t j) {
    // i and j must guaranted be in the matrix -> else index error.

    if (matrix[i][j].piles < 4) {
        return;
    }

    matrix[i][j].piles -= 4;
    
    // top
    if (!matrix.at(i - 1)) {
        matrix.push_front(Vector<Pixel>(matrix[i].size()));
        ++i;
    }
    matrix[i - 1][j].piles += 1;

    // right
    if (!matrix[i].at(j + 1)) {
        for (size_t q = 0; q != matrix.size(); ++q) {
            matrix[q].push_back(Pixel());
        }
    }
    matrix[i][j + 1].piles += 1;

    // bottom
    if (!matrix.at(i + 1)) {
        matrix.push_back(Vector<Pixel>(matrix[i].size()));
    }
    matrix[i + 1][j].piles += 1;

    // left
    if (!matrix[i].at(j - 1)) {
        for (size_t q = 0; q != matrix.size(); ++q) {
            matrix[q].push_front(Pixel());
        }
        ++j;
    }
    matrix[i][j - 1].piles += 1;
}