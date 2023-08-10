#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace neko {
	class Matrix3x3 {
	public:
		vec3 rows[3];
		// [row][column]
		// rows[0] = vec3{ 0, 0, 0 }
		// rows[1] = vec3{ 0, 0, 0 }
		// rows[2]  vec3{ 0, 0, 0,}

		Matrix3x3() = default;
		Matrix3x3(const vec3& row1, const vec3& row2, const vec3& row3) {
			rows[0] = row1;
			rows[1] = row2;
			rows[2] = row3;
		}

		vec3  operator [] (size_t index) const { return rows[index]; }
		vec3& operator [] (size_t index) { return rows[index]; }

		vec2 operator * (const vec2& v);
		Matrix3x3 operator * (const Matrix3x3& mx);

		static Matrix3x3 createTranslation(const vec2& translate);
		static Matrix3x3 createScale(const vec3& scale);
		static Matrix3x3 createScale(float scale);
		static Matrix3x3 createRotation(float radians);

		static Matrix3x3 createIdentity();

		vec2 getTranslation() const;
		float getRotation() const;
		vec2 getScale() const;
	};

	inline vec2 Matrix3x3::operator*(const vec2& v) {
		// | a b c |   | x |
		// | d e f | * | y |
		// | g h i |   | 1 |

		vec2 result;
		result.x = rows[0][0] * v.x + rows[0][1] * v.y + rows[0][2];
		result.y = rows[1][0] * v.x + rows[1][1] * v.y + rows[1][2];

		return result;
	}

	inline Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mx) {
		// | a b c |   | j k l |
		// | d e f | * | m n o |
		// | g h i |   | p q r |

		Matrix3x3 result;
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0] + rows[0][2] * mx[2][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1] + rows[0][2] * mx[2][1];
		result[0][2] = rows[0][0] * mx[0][2] + rows[0][1] * mx[1][2] + rows[0][2] * mx[2][2];

		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0] + rows[1][2] * mx[2][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1] + rows[1][2] * mx[2][1];
		result[1][2] = rows[1][0] * mx[0][2] + rows[1][1] * mx[1][2] + rows[1][2] * mx[2][2];

		result[2][0] = rows[2][0] * mx[0][0] + rows[2][1] * mx[1][1] + rows[2][2] * mx[2][0];
		result[2][1] = rows[2][0] * mx[0][1] + rows[2][1] * mx[1][1] + rows[2][2] * mx[2][1];
		result[2][2] = rows[2][0] * mx[0][2] + rows[2][1] * mx[1][2] + rows[2][2] * mx[2][2];

		return result;
	}

	inline Matrix3x3 Matrix3x3::createIdentity() {
		return {
			{ 1, 0, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 1 }
		};
	}



	inline Matrix3x3 Matrix3x3::createTranslation(const vec2& translate) {
		// | 1 0 x |
		// | 0 1 y |
		// | 0 0 1 |
		Matrix3x3 mx = createIdentity();

		mx[0][2] = translate.x;
		mx[1][2] = translate.y;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::createScale(const vec3& scale) {
		// | sx 0 0 |
		// | 0 sy 0 |
		// | 0  0 1 |
		Matrix3x3 mx = createIdentity();
		mx[0][0] = scale.x;
		mx[1][1] = scale.y;

		return mx;
	};

	inline Matrix3x3 Matrix3x3::createScale(float scale) {
		// | s 0 0 |
		// | 0 s 0 |
		// | 0 0 1 |
		Matrix3x3 mx = createIdentity();
		mx[0][0] = scale;
		mx[1][1] = scale;

		return mx;
	};

	inline Matrix3x3 neko::Matrix3x3::createRotation(float radians) {
		// | c -s 0 |
		// | s  c 0 |
		// | 0  0 1 |
		Matrix3x3 mx = createIdentity();

		float c = cos(radians);
		float s = sin(radians);

		mx[0][0] = c; mx[0][1] = -s;
		mx[1][0] = s; mx[1][1] = c;

		return mx;
	}

	inline vec2 Matrix3x3::getTranslation() const {

		return { rows[0][2], rows[1][2] };
	}

	inline float Matrix3x3::getRotation() const {

		return std::atan2(rows[1][0], rows[0][0]);
	}

	inline vec2 Matrix3x3::getScale() const {

		vec2 x = { rows[0][0], rows[0][1] };
		vec2 y = { rows[1][0], rows[1][1] };

		return { x.length(), y.length() };
	};

	using mat3 = Matrix3x3;
};