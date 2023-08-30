#pragma once
#include "FrameWork/Actor.h"
#include "FrameWork/Components/PhysicsComponent.h"
#include "Framework/Components/SpriteAnimRenderComponent.h"

namespace neko
{
	class Weapon : public neko::Actor
	{
	public:
		CLASS_DECLARATION(Weapon)

		bool initialize() override;
		void onDestroy() override;
		void update(float dt) override;

		void onCollisionEnter(Actor* other);

	private:
		float speed = 0;
		float turnRate = 0;

		class PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimRenderComponent* m_spriteAnimComponent = nullptr;
	};


}