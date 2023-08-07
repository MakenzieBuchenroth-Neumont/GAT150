#pragma once
#include "PhysicsComponent.h"

namespace neko {
	class EnginePhysicsComponent : public PhysicsComponent {
	public:
		virtual void update(float dt) override;
		virtual void applyForce(const vec2& force) override;

	};
}