#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace neko {
	void EnginePhysicsComponent::update(float dt) {
		m_owner->m_transform.position += m_velocity * dt;
		m_velocity = std::pow(1 - m_damping, dt);
	}

	void EnginePhysicsComponent::applyForce(const vec2& force) {
		m_velocity += force;
	}
}

