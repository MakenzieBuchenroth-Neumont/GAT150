#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace neko {
	class Enemy : public neko::Actor {
	public:
		CLASS_DECLARATION(Enemy)

		Enemy() = default;
		Enemy(float speed, float turnRate, const neko::Transform& transform) :
			neko::Actor{ transform },
			speed{ speed },
			jump{ jump }
		{}

		bool initialize() override;
		void update(float dt) override;
		void onCollisionEnter(Actor* other) override;
		void onCollisionExit(Actor* other) override;

	private:
		float speed = 0;
		float jump = 0;
		bool destroyed = false;

		class PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimRenderComponent* m_spriteAnimComponent = nullptr;
	};
}