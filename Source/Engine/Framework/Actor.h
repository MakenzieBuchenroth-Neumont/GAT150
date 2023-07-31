#pragma once
#include <memory>
#include "Core/Core.h"
#include "Renderer/Model.h"

namespace neko {
	class Actor {
	public:
		Actor(const neko::Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}
		Actor(const neko::Transform& transform) :
			m_transform{ transform }
		{}


		void deleteActor(); 

		virtual void update(float dt);
		virtual void draw(neko::Renderer& renderer);

		float getRadius() { return (m_model) ? m_model->getRadius() * m_transform.scale : 0; }
		virtual void onCollision(Actor* other) {}

		void addForce(const vec2& force) { m_velocity += force; }
		void setDamping(float damping) { m_damping = damping; }

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

		Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;
		bool m_destroyed = false;
	protected:
		std::shared_ptr<Model> m_model;

		vec2 m_velocity;
		float m_damping = 0;
	};
};