#pragma once
#include <list>
#include "Actor.h"

namespace neko {
	class Renderer;

	class Scene {
	public:
		Scene() = default;

		bool initialize();
		void update(float dt);
		void draw(Renderer& renderer);
		 
		void add(std::unique_ptr<Actor> actor);
		void removeAll(bool force = false);

		bool load(const std::string& filename);
		void read(const json_t& value);

		template<typename T>
		T* getActor();
		template<typename T = Actor>
		T* getActorByName(const std::string& name);


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

	template<typename T>
	inline T* Scene::getActorByName(const std::string& name) {
		for (auto& actor : m_actors) {
			if (actor->name == name) {
				T* result = dynamic_cast<T*>(actor.get());
				if (result) return result;
			}
		}

		return nullptr;
	}
}