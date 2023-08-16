#pragma once
#include "Vector3.h"
#include "Matrix3x3.h"
#include "Core/Json.h"

namespace neko {
	class Transform {
	public:
		vec2 position;
		float rotation = 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform(const vec2& position, float rotation, float scale) : 
			position{ position }, 
			rotation{ rotation }, 
			scale{ scale} 
		{}

		mat3 getMatrix() const {
			mat3 ms = mat3::createScale(scale);
			mat3 mr = mat3::createRotation(rotation);
			mat3 mt = mat3::createTranslation(position);
			mat3 mx = mt * ms * mr;

			return mx;
		}

		void read(const json_t& value);

	};
}