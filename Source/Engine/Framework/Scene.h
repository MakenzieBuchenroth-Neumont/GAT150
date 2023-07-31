#pragma once
#include <list>
#include "Actor.h"

namespace neko {
	class Renderer;

	class Scene {
	public:
		Scene() = default;

		void update(float dt);
		void draw(Renderer& renderer);

		void add(std::unique_ptr<Actor> actor);
		void removeAll();

		template<typename T>
		T* getActor();

		friend class Actor;

		std::list<std::unique_ptr<Actor>> m_actors;
	private:
	};

	template<typename T>
	inline T* Scene::getActor() {
		for (auto& actor : m_actors) {
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}
}