#pragma once
#include <cmath>
#include <sstream>

namespace neko {
	class Vector3 {
	public:
		float x, y, z;

	public:
		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
		Vector3(float v) : x{ v }, y{ v }, z{ v } {}
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
		Vector3(int x, int y, int z) : x{ (float)x }, y{ (float)y }, z{ (float)z } {}

		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		Vector3 negate() const { return Vector3(-x, -y, -z); }

		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
		Vector3 operator / (const Vector3& v) const { return Vector3(x / v.x, y / v.y, z / v.z); }
		Vector3 operator * (const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }

		Vector3 operator + (float s) const { return Vector3(x + s, y + s, z + s); }
		Vector3 operator - (float s) const { return Vector3(x - s, y - s, z + s); }
		Vector3 operator / (float s) const { return Vector3(x / s, y / s, z + s); }
		Vector3 operator * (float s) const { return Vector3(x * s, y * s, z + s); }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }

		float lengthSqr() const { return (x * x) + (y * y) + (z * z); }
		float length() const { return std::sqrt(lengthSqr()); }

		float distanceSqr(const Vector3& v) const { return (v - *this).lengthSqr(); }
		float distance(const Vector3& v) const { return (v - *this).length(); }

		Vector3 normalized() const { return *this / length(); }
		void normalize() { *this /= length(); }
		static float Dot(const Vector3& v1, const Vector3& v2);
	};

	// get the dot product beteen v1 and v2 https://www.falstad.com/dotproduct/
	inline float Vector3::Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	using vec3 = Vector3;
}
