#pragma once
#include "PhysicsComponent.h"

namespace neko {
	class EnginePhysicsComponent : public PhysicsComponent {
	public:
		CLASS_DECLARATION(EnginePhysicsComponent)
		virtual void update(float dt) override;
		virtual void applyForce(const vec2& force) override;

	};
}