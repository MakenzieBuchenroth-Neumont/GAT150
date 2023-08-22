#include "Scene.h"
#include "Framework/Components/CollisionComponent.h"

namespace neko {
	bool Scene::initialize() {
		for (auto& actor : m_actors) actor->initialize();

		return true;
	}

	void Scene::update(float dt) {
		// update and remove destroyed actors
		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {
			if ((*iter)->active) {

				(*iter)->update(dt);
			}
				iter = ((*iter)->destroyed) ? iter = m_actors.erase(iter) : ++iter;
		}

		// check collisions
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) {

			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) {

				CollisionComponent* collision1 = (*iter1)->getComponent<CollisionComponent>();
				CollisionComponent* collision2 = (*iter2)->getComponent<CollisionComponent>();

				if (collision1 == nullptr || collision2 == nullptr) continue;

				if (collision1->checkCollision(collision2)) {
					(*iter1)->onCollision(iter2->get());
					(*iter2)->onCollision(iter1->get());
				}
			}
		}
	}

	void Scene::draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			if (actor->active) actor->draw(renderer);
		}
	}

	void Scene::add(std::unique_ptr<Actor> actor) {
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::removeAll(bool force) {
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			(force || !(*iter)->persistent) ? iter = m_actors.erase(iter) : iter++;
		}
	}

	bool Scene::load(const std::string& filename) {
		rapidjson::Document document;
		if (!Json::load(filename, document)) {
			ERROR_LOG("Could not load scene file: " << filename);
			return false;
		}
		read(document);

		return true;
	}

	void Scene::read(const json_t& value) {
		if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray()) {
			for (auto& actorValue : GET_DATA(value, actors).GetArray()) {
				std::string type;
				READ_DATA(actorValue, type);

				auto actor = CREATE_CLASS_BASE(Actor, type);
				actor->read(actorValue);

				if (actor->prototype) {
					std::string name = actor->name;
					Factory::Instance().regPrototype(name, std::move(actor));
				}
				else {
					add(std::move(actor));
				}
			}
		}
	}
}