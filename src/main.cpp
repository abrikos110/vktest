#include <climits>
#if CHAR_BIT != 8
#error WAT
#endif

#include <vector>
#include <cassert>
#include <iostream>

#include "bmp.h"
#include "some_utils.h"
#include "sdf.h"

bool in_triangle(flt2 x, flt2 a, flt2 b, flt2 c) {
    return cross(x - a, b - a) > 0
        && cross(x - b, c - b) > 0
        && cross(x - c, a - c) > 0;
}

struct scene {
    unsigned w, h;
    std::vector<unsigned> image;

    scene(unsigned w, unsigned h) : w(w), h(h), image(w * h) {}

    flt4 calc_pixel(int i, int j) {
        flt4 ans{(i + 1.f) / w, (1.f + j) / h, 0.5};
        assert(ans.a * w > i);
        return in_triangle({1.f * i, 1.f * j}, {20,20}, {40,200}, {222,222})
            ? ans : flt4(1., 0.1, 0.0);
    }

    void render() {
        for (unsigned i = 0; i < w; ++i) {
            for (unsigned j = 0; j < h; ++j) {
                image[i*h + j] = rgb(calc_pixel(i, j));
                assert(image[i*h + j] > 0);
            }
        }
    }

    void save_bmp(const char *fname) {
        SaveBMP(fname, image.data(), w, h);
    }
};

int main() {
    scene S(256, 256);
    S.render();
    S.save_bmp("answer.bmp");

    std::cout << "Done!" << std::endl;
    return 0;
}
