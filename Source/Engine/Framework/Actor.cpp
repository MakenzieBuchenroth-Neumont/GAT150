#include "Actor.h"
#include "Components/RenderComponent.h"

namespace neko {
	CLASS_DEFINITION(Actor)

	bool Actor::initialize() {
		for (auto& component : components) {
			component->initialize();
		}

		return true;
	}

	void Actor::onDestroy() {
		for (auto& component : components) {
			component->onDestroy();
		}
	}

	void Actor::update(float dt) {
		if (lifespan != -1.0f) {
			lifespan -= dt;
			destroyed = (lifespan <= 0);
		}

		for (auto& component : components) {
			component->update(dt);
		}

	}

	void Actor::draw(neko::Renderer& renderer) {
		for (auto& component : components) {
			if (dynamic_cast<RenderComponent*>(component.get())) {
				dynamic_cast<RenderComponent*>(component.get())->draw(renderer);
			}
		}
	}

	void Actor::addComponent(std::unique_ptr<Component> component) {
		component->m_owner = this;
		components.push_back(std::move(component));
	}

	void Actor::deleteActor() {
		delete this;
	}

	void Actor::read(const json_t& value) {
		Object::read(value);
		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		if (HAS_DATA(value, transform)) transform.read(value);

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray()) {
			for (auto& componentValue : GET_DATA(value, components).GetArray()) {
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type);
				component->read(componentValue);
				addComponent(std::move(component));
			}
		}
	}
}