#pragma once
#include "MathUtils.h"
#include <cmath>

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color() = default;
    Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    float  operator [] (unsigned int index) const { return (&r)[index]; }
    float& operator [] (unsigned int index) { return (&r)[index]; }

    Color Add(Color v) { return Color{ r + v.r, g + v.g, b + v.b, a + v.a }; }
    Color operator + (const Color& c) const { return Color{ r + c.r, g + c.g, b + c.b, a + c.a }; }
    Color operator - (const Color& c) const { return Color{ r - c.r, g - c.g, b - c.b, a - c.a }; }
    Color operator * (const Color& c) const { return Color{ r * c.r, g * c.g, b * c.b, a * c.a }; }
    Color operator / (const Color& c) const { return Color{ r / c.r, g / c.g, b / c.b, a / c.a }; }

    Color operator + (float s) const { return Color{ r + s, g + s, b + s, a + s }; }
    Color operator - (float s) const { return Color{ r - s, g - s, b - s, a - s }; }
    Color operator * (float s) const { return Color{ r * s, g * s, b * s, a * s }; }
    Color operator / (float s) const { return Color{ r / s, g / s, b / s, a / s }; }
};
