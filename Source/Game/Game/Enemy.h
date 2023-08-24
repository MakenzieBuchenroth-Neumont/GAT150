#pragma once
#include "Core/Json.h"
#include "Framework/Factory.h"
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace neko {
	class Enemy : public neko::Actor {
	public:
		CLASS_DECLARATION(Enemy)

		Enemy() = default;
		Enemy(float speed, float turnRate, const neko::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			m_turnRate{ turnRate }
		{
			m_fireRate = 2.0f;
			m_fireTimer = m_fireRate;
		}

		bool initialize() override;
		void update(float dt) override;
		void onCollisionEnter(neko::Actor* other);


	private:
		float speed = 0;
		float m_turnRate = 0;

		float m_fireRate = 0;
		float m_fireTimer = 0;
		float m_health = 10;

		neko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}