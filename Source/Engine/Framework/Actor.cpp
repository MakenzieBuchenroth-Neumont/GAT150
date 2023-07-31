#include "Actor.h"

namespace neko {
	void Actor::update(float dt) {
		if (m_lifespan != -1.0f) {
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		m_transform.position += m_velocity * dt;
		m_velocity = std::pow(1 - m_damping, dt);
	}

	void Actor::draw(neko::Renderer& renderer) {
		m_model->draw(renderer, m_transform);
	}

	void Actor::deleteActor() {
		delete this;
	}
}