#pragma once
#include "Vector2.h"
#include "Matrix2x2.h"

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

		mat2 getMatrix() const {
			mat2 ms = mat2::createScale(scale);
			mat2 mr = mat2::createRotation(rotation);

			return ms * mr;
		}

	private:
	};
}