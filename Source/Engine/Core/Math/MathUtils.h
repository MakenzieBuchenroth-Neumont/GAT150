#pragma once
#include <math.h>

namespace neko {
	constexpr float pi = 3.14159265359f;
	constexpr float twoPi = 6.28318530718f;
	constexpr float halfPi = 1.57079632679f;

	constexpr float radiansToDegrees(float radians) { return radians * (180.0f / pi); }
	constexpr float degreesToRadians(float degrees) { return degrees * (pi / 180.0f); }

	constexpr int wrap(int value, int max) {
		return (value % max) + ((value < 0) ? max : 0);
	}

	template <typename T>
	inline T max(T a, T b) {
		return (a > b) ? a : b;
	}

	template <typename T>
	inline T min(T a, T b) {
		return (a < b) ? a : b;
	}

	template <typename T>
	inline T clamp(T value, T min, T max) {
		if (min > max) std::swap(min, max);

		if (value < min) value = min;
		else if (value > max) value = max;

		return value;
	}
	
	template<typename T>
	constexpr T lerp(const T& a, const T& b, float t)
	{
		return (a * (1.0f - t)) + (b * t);
	}
}