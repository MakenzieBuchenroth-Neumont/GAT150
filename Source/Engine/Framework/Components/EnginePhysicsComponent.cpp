#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace neko {
	CLASS_DEFINITION(EnginePhysicsComponent)

	void EnginePhysicsComponent::update(float dt) {
		m_owner->transform.position += m_velocity * dt;
		m_velocity = std::pow(1 - m_damping, dt);
	}

	void EnginePhysicsComponent::applyForce(const vec2& force) {
		m_velocity += force;
	}
}

