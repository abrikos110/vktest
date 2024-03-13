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
    std::vector<flt4> rays;

    scene(unsigned w, unsigned h, float vfov = 90)
        : w(w), h(h), image(w * h), rays(w * h) {
        // camera at (0,0,0) watching to (0,0,1)
        // x direction is (1,0,0), y direction is (0,1,0)
        // image coords are from -1 to 1 for y and from -w/h to w/h for x
        flt4 dir{0, 0, 1};
        vfov *= M_PI / 180;
        for (unsigned i = 0; i < w; ++i) {
            for (unsigned j = 0; j < h; ++i) {
                flt4 r(i2x(i), j2y(j), 0);
                float n = std::sqrt(dot(r, r));
                r /= (n ? n : 1);
                float angle = n * vfov / 2;
                rays[i*h + j] = std::cos(angle) * dir + std::sin(angle) * r;
            }
        } // TODO stupid_tracing
    }

    float i2x(unsigned i) { return (2.f * i - w) / h; }
    float j2y(unsigned j) { return (2.f * j - h) / h; }

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
