#pragma once
#include <cmath>

namespace Math
{
	constexpr float Pi		= 3.14159265359f; // 180
	constexpr float TwoPi	= 6.28318530718f; // 360
	constexpr float HalfPi	= 1.57079632679f; // 90

	constexpr float RadToDeg(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegToRad(float degrees) { return degrees * (Pi / 180.0f); }


	inline float Sin(float radians)
	{
		return std::sinf(radians);
	}

	inline float Cos(float radians)
	{
		return std::cosf(radians);
	}

	inline float Sqrt(float value)
	{
		return std::sqrtf(value);
	}

	inline float Atan2(float y, float x)
	{
		std::atan2f(y, x);
	}

	/// <summary>
	/// Returns the maximum value of a and b
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a">value</param>
	/// <param name="b">value</param>
	/// <returns>The maximum value beteen a and b.</returns>
	template<typename T>
	T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	/// <summary>
	/// Returns the minimum value of a and b
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a">value</param>
	/// <param name="b">value</param>
	/// <returns>The minimum value beteen a and b.</returns>
	template<typename T>
	T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	/// <summary>
	/// Returns the absolute value of the input
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value">value</param>
	/// <returns>The absolute value of the input</returns>
	template<typename T>
	T absValue(T value)
	{
		return (value > 0) ? -value : value;
	}

	template<typename T>
	inline T Clamp(T v, T min, T max)
	{
		return (v < min) ? min : ((v > min) ? max : v);

	}
}