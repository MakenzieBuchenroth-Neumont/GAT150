#include "Player.h"
#include "Weapon.h"
#include "H_AsteroidField.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Components/ModelRenderComponent.h"
#include <Framework/Components/PhysicsComponent.h>


void Player::update(float dt) {
	Actor::update(dt);
	neko::vec2 forward = neko::vec2{ 0, 0 };

	auto physicsComponent = getComponent<neko::PhysicsComponent>();
	//physicsComponent->applyForce(forward * m_speed * thrust);
	
	if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_W)) forward += {0, -1};
	if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_S)) forward += {0, 1};

	if ((std::fabs(forward.x) + std::fabs(forward.y)) == 2);

	m_transform.position += forward * m_speed * neko::g_time.getDeltaTime();

	if (m_transform.position.y >= neko::g_renderer.getHeight()) {
		m_transform.position.y = neko::g_renderer.getHeight();
	}
	if (m_transform.position.y <= 0) {
		m_transform.position.y = 0;
	}

}

void Player::onCollision(Actor* other) {
	if (other->m_tag == "Enemy") {
	// particle system variables
	if (!dead) {
		neko::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = neko::pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;

		data.color = neko::Color{ 1, 1, 1, 1 };

		neko::Transform transform{ { m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<neko::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_game->m_scene->add(std::move(emitter));
		dead = true;
	}

	dynamic_cast<H_AsteroidField*>(m_game)->setState(H_AsteroidField::eState::PlayerDeadStart);
	m_destroyed = true;

	}
	if (other->m_tag == "Powerup") {
		dynamic_cast<H_AsteroidField*>(m_game)->m_powerup = true;
		other->m_destroyed = true;
	}
}
