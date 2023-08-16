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
#include "Framework/Components/CollisionComponent.h"


bool Player::initialize() {
	Actor::initialize();

	// cache off
	m_physicsComponent = getComponent<neko::PhysicsComponent>();
	auto collisionComponent = getComponent<neko::CollisionComponent>();
	if (collisionComponent) {
		auto renderComponent = getComponent<neko::RenderComponent>();
		if (renderComponent) {
			float scale = transform.scale;
			collisionComponent->m_radius = renderComponent->getRadius() * scale * 0.7f;;
		}
	}

	return false;
}

void Player::update(float dt) {
	Actor::update(dt);
	neko::vec2 forward = neko::vec2{ 0, 0 };

	//m_physicsComponent->applyForce(forward * m_speed * thrust);
	
	if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_W)) forward += {0, -1};
	if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_S)) forward += {0, 1};

	if ((std::fabs(forward.x) + std::fabs(forward.y)) == 2) {}

	transform.position += forward * speed * neko::g_time.getDeltaTime();

	if (transform.position.y >= neko::g_renderer.getHeight()) {
		transform.position.y = (float)neko::g_renderer.getHeight();
	}
	if (transform.position.y <= 0) {
		transform.position.y = 0;
	}

}

void Player::onCollision(Actor* other) {
	if (other->tag == "Enemy") {
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

		neko::Transform transform{ { transform.position }, 0, 1 };
		auto emitter = std::make_unique<neko::Emitter>(transform, data);
		emitter->lifespan = 1.0f;
		m_game->m_scene->add(std::move(emitter));
		dead = true;
	}

	dynamic_cast<H_AsteroidField*>(m_game)->setState(H_AsteroidField::eState::PlayerDeadStart);
	destroyed = true;

	}
	if (other->tag == "Powerup") {
		dynamic_cast<H_AsteroidField*>(m_game)->m_powerup = true;
		other->destroyed = true;
	}
}
