#include "Scene.h"

namespace neko {
	void Scene::update(float dt) {
		// update and destroyed remove actors
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			(*iter)->update(dt);
			((*iter)->m_destroyed) ? iter = m_actors.erase(iter) : iter++;
		}

		// check collisions
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) {
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) {
				float distance = (*iter1)->m_transform.position.distance((*iter2)->m_transform.position);
				float radius = (*iter1)->getRadius() + (*iter2)->getRadius();

				if (distance <= radius) {
					(*iter1)->onCollision(iter2->get());
					(*iter2)->onCollision(iter1->get());
				}
			}
		}
	}

	void Scene::draw(Renderer& renderer) {
		for (auto& actor : m_actors) actor->draw(renderer);
	}

	void Scene::add(std::unique_ptr<Actor> actor) {
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::removeAll() {
		m_actors.clear();
	}
}