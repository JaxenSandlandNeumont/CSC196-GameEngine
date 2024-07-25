#pragma once
#include "MathUtils.h"
#include <cmath>
#include <stdint.h>

struct Color
{
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 0.0f;


    enum class colorPresets
    {
        yellow,
        red,
        blue,
        cyan,
        pink,
        green,
        white,
        black
    };

    Color() = default;
    Color(colorPresets preset)
    {
        switch (preset)
        {
            case Color::colorPresets::red:
            {
                 r = 1.0f;
            }
            break;


            case Color::colorPresets::green:
            {
                g = 1.0f;
            }
            break;

            case Color::colorPresets::yellow:
            {
                r = 1.0f;
                g = 1.0f;
            }
            break;

            case Color::colorPresets::blue:
            {
                b = 1.0f;
            }

            case Color::colorPresets::pink:
            {
                r = 1.0f;
                b = 1.0f;
            }
            break;

            case Color::colorPresets::cyan:
            {
                g = 1.0f;
                b = 1.0f;
            }
            break;

            case Color::colorPresets::white:
            {
                r = 1.0f;
                g = 1.0f;
                b = 1.0f;
            }
            break;

            case Color::colorPresets::black:
            {
            }
            break;

            default:
            {

            }
            break;
        }
    }

    Color(float r, float g, float b, float a = 0)
    {
        this->r = r; // c - 25, 0 - 1
        this->g = g;
        this->b = b;
        this->a = a;
    }



    float  operator [] (unsigned int index) const { return (&r)[index]; }
    float& operator [] (unsigned int index) { return (&r)[index]; }


    Color operator + (const Color& c) const { return Color{ r + c.r, g + c.g, b + c.b, a + c.a }; }
    Color operator - (const Color& c) const { return Color{ r - c.r, g - c.g, b - c.b, a - c.a }; }
    Color operator * (const Color& c) const { return Color{ r * c.r, g * c.g, b * c.b, a * c.a }; }
    Color operator / (const Color& c) const { return Color{ r / c.r, g / c.g, b / c.b, a / c.a }; }

    Color operator + (float s) { return Color{ r + s, g + s, b + s, a + s }; }
    Color operator - (float s) { return Color{ r - s, g - s, b - s, a - s }; }
    Color operator * (float s) { return Color{ r * s, g * s, b * s, a * s }; }
    Color operator / (float s) { return Color{ r / s, g / s, b / s, a / s }; }

    Color operator = (const Color& c) { return Color{ r = c.r, g = c.g, b = c.b, a = c.a }; }
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
