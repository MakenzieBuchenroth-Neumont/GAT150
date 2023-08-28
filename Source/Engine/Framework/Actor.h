#pragma once
#include <memory>
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include "Framework/Object.h"

namespace neko {
	class Actor : public Object {
	public:
		CLASS_DECLARATION(Actor)
		Actor() = default;
		Actor(const neko::Transform& transform) :
			transform{ transform }
		{}
		Actor(const Actor& other);
		virtual ~Actor() {
			onDestroy();
		}

		virtual bool initialize() override;
		virtual void onDestroy() override;

		void deleteActor();

		virtual void update(float dt);
		virtual void draw(neko::Renderer& renderer);

		void addComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* getComponent();

		virtual void onCollisionEnter(Actor* other) {}
		virtual void onCollisionExit(Actor* other) {}

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

	public:
		Transform transform;
		std::string tag;
		float lifespan = -1.0f;
		bool destroyed = false;
		bool persistent = false;
		bool prototype = false;

	protected:
		std::vector<std::unique_ptr<Component>> components;
	};

	template<typename T>
	inline T* Actor::getComponent() {
		for (auto& component : components) {
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
};