#include "image.h"

Color::Color(float _r, float _g, float _b) {
    r = _r;
    g = _g;
    b = _b;
}

void Export(const Vector<Vector<Pixel>>& matrix, const std::string& _path, const std::string& filename) {
    /*
    @_path - current path to output directory
    @filename - name of file, which is going to be created
    */

    std::filesystem::path path{_path};
    if (!std::filesystem::exists(path)) {
        std::cout << "\e[1;33mIndicate output path don't exist. Do you want to create it?\e[0;0m\n";
        std::cout << "Path: " << _path << '\n';
        std::cout << "(y / n) ";
        char answer;
        std::cin >> answer;
        if (answer == 'n') {
            return;
        }
        std::filesystem::create_directories(_path);
    }

    path /= filename;
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    
    if (!f.is_open()) {
        std::cerr << "\e[1;31m[ERROR] Export could not be did.\e[0;0m\n";
        return;
    }

    size_t width = matrix[0].size();
    size_t height = matrix.size();
    const int colorsPaletteSize = 64;
    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize = fileHeaderSize + informationHeaderSize + colorsPaletteSize + std::ceil(width * height * (0.5));

    unsigned char fileHeader[fileHeaderSize];

    // File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    // File size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    // Reserved 1 (Not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    // Reserved 1 (Not used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // Pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize + colorsPaletteSize;
    fileHeader[11] = (fileHeaderSize + informationHeaderSize + colorsPaletteSize) >> 8;
    fileHeader[12] = (fileHeaderSize + informationHeaderSize + colorsPaletteSize) >> 16;
    fileHeader[13] = (fileHeaderSize + informationHeaderSize + colorsPaletteSize) >> 24;

    unsigned char palette[colorsPaletteSize];

    Color _colors[5] = {
        Color {250, 250, 250},  // white
        Color {0, 102, 0},  // green
        Color {204, 0, 204},  // purple
        Color {253, 220, 7},  // yellow
        Color {32, 32, 32}  // black
    };

    for (int i = 0; i != 5; ++i) {  // 5 - colors size
        palette[4 * i + 0] = _colors[i].b;
        palette[4 * i + 1] = _colors[i].g;
        palette[4 * i + 2] = _colors[i].r;
        palette[4 * i + 3] = 0;
    }
    for (int i = 20; i != 64; ++i) {  // define 0 as the default value
        palette[i] = 0;
    }

    unsigned char informationHeader[informationHeaderSize];

    // Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;
    // Image width
    informationHeader[4] = width;
    informationHeader[5] = width >> 8;
    informationHeader[6] = width >> 16;
    informationHeader[7] = width >> 24;
    // Image height
    informationHeader[8] = height;
    informationHeader[9] = height >> 8;
    informationHeader[10] = height >> 16;
    informationHeader[11] = height >> 24;
    // Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;
    // Bits per pixel
    informationHeader[14] = 4;
    informationHeader[15] = 0;
    // Compression (No compression)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;
    // Image size (No compression)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;
    // X pixels per meter (Not specified)
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;
    // Y pixels per meter (No compression)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;
    // Total color
    informationHeader[32] = 5;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;
    // Important colors (Generally ignored)
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);
    f.write(reinterpret_cast<char*>(palette), colorsPaletteSize);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; x += 2) {
            unsigned char pixel = 0;
            pixel |= GetColorIndex(matrix, x, y) << 4;
            if (x + 1 != width) {
                pixel |= GetColorIndex(matrix, x + 1, y);
            }
            f.write(reinterpret_cast<char*>(&pixel), 1);
        }
        f.write("\0\0\0", (4 - ((int)std::ceil(width * 0.5) % 4)) % 4);
    }

    f.close();
}

uint8_t GetColorIndex(const Vector<Vector<Pixel>>& matrix, uint64_t x, uint64_t y) {
    if (matrix[y][x].piles > 3) {
        return 4;
    }
    return static_cast<uint8_t>(matrix[y][x].piles);
}