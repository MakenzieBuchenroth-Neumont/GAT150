#include "EnemyComponent.h"
#include "Player.h"
#include "Weapon.h"
#include "H_AsteroidField.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

bool EnemyComponent::initialize() {

	auto collisionComponent = m_owner->getComponent<neko::CollisionComponent>();
	if (collisionComponent) {
		auto renderComponent = m_owner->getComponent<neko::RenderComponent>();
		if (renderComponent) {
			float scale = m_owner->transform.scale;
			collisionComponent->m_radius = renderComponent->getRadius() * scale;
		}
	}

	return true;
}

void EnemyComponent::update(float dt) {

	Player* player = m_owner->m_scene->getActor<Player>();
	if (player) {
		neko::Vector2 direction = player->transform.position - m_owner->transform.position;
		m_owner->transform.rotation = direction.angle() + neko::halfPi;
	}
	neko::vec2 forward = neko::vec2{ -1, 0 };
	speed = 75;
	m_owner->transform.position += forward * speed * neko::g_time.getDeltaTime();
}

void EnemyComponent::onCollision(neko::Actor* other) {
	//
}

void EnemyComponent::read(const neko::json_t & value) {
	READ_DATA(value, speed);
}
