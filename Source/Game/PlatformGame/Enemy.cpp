#include "Enemy.h"
#include "Boing.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Components/ModelRenderComponent.h"
#include <Framework/Components/PhysicsComponent.h>
#include "Framework/Components/CollisionComponent.h"


namespace neko {
	CLASS_DEFINITION(Enemy)

		bool Enemy::initialize() {
		Actor::initialize();

		// cache off
		m_physicsComponent = getComponent<neko::PhysicsComponent>();

		return false;
	}

	void Enemy::update(float dt) {
		Actor::update(dt);

		float dir = 0;

		neko::vec2 forward = neko::vec2{ 1, 0 };

		m_physicsComponent->applyForce(forward * speed * dir);

		//jump}

	}

	void Enemy::onCollisionEnter(Actor* other) {
	}

	void Enemy::onCollisionExit(Actor* other) {
	}

	void Enemy::read(const json_t& value) {
		Actor::read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}
