#pragma once
#include "MathUtils.h"
#include <cmath>
#include <stdint.h>

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color() = default;
    Color(float r, float g, float b, float a = 0)
    {
        this->r = r; // c - 25, 0 - 1
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

    Color operator + (float s) { return Color{ r + s, g + s, b + s, a + s }; }
    Color operator - (float s) { return Color{ r - s, g - s, b - s, a - s }; }
    Color operator * (float s) { return Color{ r * s, g * s, b * s, a * s }; }
    Color operator / (float s) { return Color{ r / s, g / s, b / s, a / s }; }

    Color operator += (const Color& c) { return Color{ r += c.r, g += c.g, b += c.b, a += c.a }; }
    Color operator -= (const Color& c) { return Color{ r -= c.r, g -= c.g, b -= c.b, a -= c.a }; }
    Color operator *= (const Color& c) { return Color{ r *= c.r, g *= c.g, b *= c.b, a *= c.a }; }
    Color operator /= (const Color& c) { return Color{ r /= c.r, g /= c.g, b /= c.b, a /= c.a }; }
                    
    Color operator += (float s) { return Color{ r += s, g += s, b += s, a += s }; }
    Color operator -= (float s) { return Color{ r -= s, g -= s, b -= s, a -= s }; }
    Color operator *= (float s) { return Color{ r *= s, g *= s, b *= s, a *= s }; }
    Color operator /= (float s) { return Color{ r /= s, g /= s, b /= s, a /= s }; }

    static uint8_t ToInt(float c) { return static_cast<uint8_t>(Math::Clamp(c, 0.0f, 1.0f) * 255); }
};
