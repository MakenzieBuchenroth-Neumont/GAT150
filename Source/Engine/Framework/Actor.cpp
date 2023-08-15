#include "Actor.h"
#include "Components/RenderComponent.h"

namespace neko {
	CLASS_DEFINITION(Actor)

	bool Actor::initialize() {
		for (auto& component : m_components) {
			component->initialize();
		}

		return true;
	}

	void Actor::onDestroy() {
		for (auto& component : m_components) {
			component->onDestroy();
		}
	}

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

	bool Actor::read(const rapidjson::Value& value) {
		return true;
	}
}