#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/SpriteAnimRenderComponent.h"

namespace neko {
	class Player : public neko::Actor {
	public:
		CLASS_DECLARATION(Player)

		Player() = default;
		Player(float speed, float turnRate, const neko::Transform& transform) :
			neko::Actor{ transform },
			speed{ speed }
		{}

		bool initialize() override;
		void update(float dt) override;
		void onCollisionEnter(Actor* other) override;
		void onCollisionExit(Actor* other) override;

	private:
		float speed = 0;

		class PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimRenderComponent* m_spriteAnimComponent = nullptr;
	};
}