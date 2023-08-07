#pragma once
#include <memory>
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"

namespace neko {
	class Actor {
	public:
		Actor() = default;
		Actor(const neko::Transform& transform) :
			m_transform{ transform }
		{}

		void deleteActor(); 

		virtual void update(float dt);
		virtual void draw(neko::Renderer& renderer);

		void addComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* getComponent();

		float getRadius() { return 30.0f; }
		virtual void onCollision(Actor* other) {}

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

		Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;
		bool m_destroyed = false;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;
	};

	template<typename T>
	inline T* Actor::getComponent() {
		for (auto& component : m_components) {
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
};