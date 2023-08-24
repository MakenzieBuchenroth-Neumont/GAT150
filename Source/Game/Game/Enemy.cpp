#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "H_AsteroidField.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

namespace neko {
	CLASS_DEFINITION(Enemy)

		bool Enemy::initialize() {
		Actor::initialize();

		m_physicsComponent = getComponent<neko::PhysicsComponent>();

		auto collisionComponent = getComponent<neko::CollisionComponent>();
		if (collisionComponent) {
			
		}

		return true;
	}

	void Enemy::update(float dt) {

		Actor::update(dt);

		Player* player = m_scene->getActor<Player>();
		if (player) {
			neko::Vector2 direction = player->transform.position - transform.position;
			transform.rotation = direction.angle() + neko::halfPi;
		}
		neko::vec2 forward = neko::vec2{ -1, 0 };
		speed = 75;
		//transform.position += forward * speed * neko::g_time.getDeltaTime();

		m_physicsComponent->applyForce(forward * speed);
	}

	void Enemy::onCollisionEnter(neko::Actor* other) {
		//
	}

	void Enemy::read(const neko::json_t& value) {
		Actor::read(value);

		READ_DATA(value, speed);
	}
}