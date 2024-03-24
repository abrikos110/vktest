#ifndef SOME_UTILS_H
#define SOME_UTILS_H

typedef unsigned char uc;

struct flt2 {
    float a, b;
    flt2(float a, float b) : a(a), b(b) {}
    flt2(float z = 0.f) : a(z), b(z) {}
    flt2 operator+(const flt2 &o) const { return {a + o.a, b + o.b}; }
    flt2 operator-(const flt2 &o) const { return {a - o.a, b - o.b}; }
    flt2 operator*(const flt2 &o) const { return {a * o.a, b * o.b}; }
    flt2 operator/(const flt2 &o) const { return {a / o.a, b / o.b}; }
};

float cross(const flt2 &x, const flt2 &y) {
    return x.a * y.b - x.b * y.a;
}

float dot(const flt2 &x, const flt2 &y) {
    return x.a * y.a + x.b * y.b;
}

struct flt4 {
    float a, b, c, d;
    flt4(float a, float b, float c, float d = 0.f) : a(a), b(b), c(c), d(d) {}
    flt4(float z = 0.f) : a(z), b(z), c(z), d(z) {}
    flt4 operator+(const flt4 &o) const { return {a + o.a, b + o.b, c + o.c, d + o.d}; }
    flt4 operator-(const flt4 &o) const { return {a - o.a, b - o.b, c - o.c, d - o.d}; }
    flt4 operator*(const flt4 &o) const { return {a * o.a, b * o.b, c * o.c, d * o.d}; }
    flt4 operator/(const flt4 &o) const { return {a / o.a, b / o.b, c / o.c, d / o.d}; }

    float dot(const flt4 &o) {
        return a*o.a + b*o.b + c*o.c + d*o.d;
    }
};

float dot(const flt4 &x, const flt4 &y) {
    return x.a * y.a + x.b * y.b + x.c * y.c + x.d * y.d;
}

unsigned rgb(uc r, uc g, uc b) {
    return r | (g << 8) | (b << 16);
}
float clip(float x, float a = 0, float b = 1) {
    if (x < a) return a;
    if (x > b) return b;
    return x;
}
unsigned rgb(flt4 c) {
    return rgb((uc)(clip(c.a) * 255),
        (uc)(clip(c.b) * 255), (uc)(clip(c.c) * 255));
}

#endif
