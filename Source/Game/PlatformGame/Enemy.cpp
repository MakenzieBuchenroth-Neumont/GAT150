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
#include "Enemy.h"
#include "Player.h"


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

		neko::vec2 forward = neko::vec2{ 0, -1 }.rotate(transform.rotation);
		Player* player = m_scene->getActor<Player>();
		if (player)
		{
			neko::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->applyForce(direction.normalized() * speed);
		}


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
