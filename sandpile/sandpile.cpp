#include "sandpile.h"

bool Collapse(Sandpile& sandpile, size_t i, size_t j) {
    // i and j must guaranted be in the matrix -> else index error.

    Vector<Vector<Pixel>>& matrix = sandpile.matrix;

    if (matrix[i][j].piles < 4) {
        return false;
    }

    matrix[i][j].piles -= 4;
    sandpile.unstables -= matrix[i][j].piles < 4 ? 1 : 0;

    // top
    if (!matrix.at(i - 1)) {
        matrix.push_front(Vector<Pixel>(matrix[i].size()));
        ++i;
    }
    matrix[i - 1][j].piles += 1;
    sandpile.add_unstables(i - 1, j);

    // right
    if (!matrix[i].at(j + 1)) {
        for (size_t q = 0; q != matrix.size(); ++q) {
            matrix[q].push_back(Pixel());
        }
    }
    matrix[i][j + 1].piles += 1;
    sandpile.add_unstables(i, j + 1);

    // bottom
    if (!matrix.at(i + 1)) {
        matrix.push_back(Vector<Pixel>(matrix[i].size()));
    }
    matrix[i + 1][j].piles += 1;
    sandpile.add_unstables(i + 1, j);

    // left
    if (!matrix[i].at(j - 1)) {
        for (size_t q = 0; q != matrix.size(); ++q) {
            matrix[q].push_front(Pixel());
        }
        ++j;
    }
    matrix[i][j - 1].piles += 1;
    sandpile.add_unstables(i, j - 1);

    return true;
}

void Shake(Sandpile& sandpile, const Args& args) {
    size_t i = 0, j = 0, curr_iter = 0;

    while((curr_iter < args.max_iter && args.max_iter != 0) || !sandpile.is_stable()) {
        if (Collapse(sandpile, i, j)) {
            ++curr_iter;
            if (args.freq && curr_iter % args.freq == 0 && args.max_iter - curr_iter != 1) {
                Export(sandpile.matrix, args.output_path, "sandpile-" + std::to_string(curr_iter) + ".bmp");
            }
        }
        if (j == sandpile.matrix[0].size() - 1) {
            i = ++i % sandpile.matrix.size();
        }
        j = ++j % sandpile.matrix[0].size();
    }
}
