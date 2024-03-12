#include <climits>
#if CHAR_BIT != 8
#error WAT
#endif

#include "bmp.h"

typedef unsigned char uc;

struct flt2 {
    float a, b;
    flt2 operator+(const flt2 &o) const { return {a + o.a, b + o.b}; }
    flt2 operator-(const flt2 &o) const { return {a - o.a, b - o.b}; }
    flt2 operator*(const flt2 &o) const { return {a * o.a, b * o.b}; }
    flt2 operator/(const flt2 &o) const { return {a / o.a, b / o.b}; }
};
struct flt4 {
    float a, b, c, d;
    flt4 operator+(const flt4 &o) const { return {a + o.a, b + o.b, c + o.c, d + o.d}; }
    flt4 operator-(const flt4 &o) const { return {a - o.a, b - o.b, c - o.c, d - o.d}; }
    flt4 operator*(const flt4 &o) const { return {a * o.a, b * o.b, c * o.c, d * o.d}; }
    flt4 operator/(const flt4 &o) const { return {a / o.a, b / o.b, c / o.c, d / o.d}; }
};

unsigned rgb(uc r, uc g, uc b) {
    return r | (g << 8) | (b << 16);
}
float clip(float x, float a = 0, float b = 1) {
    if (x < a) return a;
    if (x > b) return b;
    return x;
}
unsigned rgb(flt4 c) {
    return rgb(clip(uc(c.a * 255)),
        clip(uc(c.b * 255)), clip(uc(c.c * 255)));
}

float cross(flt2 x, flt2 y) {
    return x.a * y.b - x.b * y.a;
}

bool in_triangle(flt2 x, flt2 a, flt2 b, flt2 c) {
    return cross(x - a, b - a) > 0
        && cross(x - b, c - b) > 0
        && cross(x - c, a - c) > 0;
}


int main() {
    const int w = 256, h = 256;
    unsigned img[w*h] = {0};
    for (unsigned i = 0; i < w; ++i) {
        for (unsigned j = 0; j < h; ++j) {
            img[i*h + j] = rgb(flt4{i * 1.f / w, j * 1.f / h, 0.5})
                * in_triangle({1.f*i,1.f*j}, {20, 20}, {40,200}, {300,300});
        }
    }
    SaveBMP("answer.bmp", (unsigned *)(void *)img, w, h);
    return 0;
}
