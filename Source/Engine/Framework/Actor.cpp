#include "Actor.h"
#include "Components/RenderComponent.h"

namespace neko {
	void Actor::update(float dt) {
		if (m_lifespan != -1.0f) {
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		for (auto& component : m_components) {
			component->update(dt);
		}

	}

	void Actor::draw(neko::Renderer& renderer) {
		for (auto& component : m_components) {
			if (dynamic_cast<RenderComponent*>(component.get())) {
				dynamic_cast<RenderComponent*>(component.get())->draw(renderer);
			}
		}
	}

	void Actor::addComponent(std::unique_ptr<Component> component) {
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}

	void Actor::deleteActor() {
		delete this;
	}
}