#include "Enemy.h"
#include "Powerup.h"
#include "Weapon.h"
#include "H_AsteroidField.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Player.h"

bool Powerup::initialize()
{
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

void Powerup::update(float dt) {

	Actor::update(dt);

	neko::vec2 forward = neko::vec2{ -1, 0 };
	m_speed = 75;
	m_transform.position += forward * m_speed * neko::g_time.getDeltaTime();
}

void Powerup::onCollision(Actor* other) {
	
}
