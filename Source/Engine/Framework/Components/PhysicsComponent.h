#pragma once
#include "Component.h"
#include <Core/math/Vector2.h>

namespace neko {
	class PhysicsComponent : public Component {
	public:
		virtual void applyForce(const vec2& force) = 0;

	public:
		vec2 m_velocity;
		vec2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;
	};
}