#include "Enemy.h"
#include "Powerup.h"
#include "Weapon.h"
#include "H_AsteroidField.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Player.h"

void Powerup::update(float dt) {

	Actor::update(dt);

	neko::vec2 forward = neko::vec2{ -1, 0 };
	m_speed = 75;
	m_transform.position += forward * m_speed * neko::g_time.getDeltaTime();
}

void Powerup::onCollision(Actor* other) {
	
}
