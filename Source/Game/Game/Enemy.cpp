#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "H_AsteroidField.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

bool Enemy::initialize() {
	Actor::initialize();

	auto collisionComponent = getComponent<neko::CollisionComponent>();
	if (collisionComponent) {
		auto renderComponent = getComponent<neko::RenderComponent>();
		if (renderComponent) {
			float scale = m_transform.scale;
			collisionComponent->m_radius = renderComponent->getRadius() * scale;
		}
	}

	return true;
}

void Enemy::update(float dt) {

	Actor::update(dt);

	Player* player = m_scene->getActor<Player>();
	if (player) {
		neko::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.angle() + neko::halfPi;
	}
	neko::vec2 forward = neko::vec2{ -1, 0 };
	m_speed = 75;
	m_transform.position += forward * m_speed * neko::g_time.getDeltaTime();
}

void Enemy::onCollision(Actor* other) {
	//
}
