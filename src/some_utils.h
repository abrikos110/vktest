#ifndef SOME_UTILS_H
#define SOME_UTILS_H

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

#endif
