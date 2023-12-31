#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace neko {
	class Player : public neko::Actor {
	public:
		CLASS_DECLARATION(Player)

		Player() = default;
		Player(float speed, float turnRate, const neko::Transform& transform) :
			neko::Actor{ transform },
			speed{ speed },
			m_turnRate{ turnRate }
		{}

		bool initialize() override;
		void update(float dt) override;
		void onCollisionEnter(Actor* other) override;

	private:
		float speed = 0;
		float m_turnRate = 0;
		float m_health = 100;
		bool dead = false;

		neko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}