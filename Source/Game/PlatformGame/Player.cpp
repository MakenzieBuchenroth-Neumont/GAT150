#include "Player.h"
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
	CLASS_DEFINITION(Player)

		bool Player::initialize() {
		Actor::initialize();

		// cache off
		m_physicsComponent = getComponent<neko::PhysicsComponent>();

		return false;
	}

	void Player::update(float dt) {
		Actor::update(dt);

		float dir = 0;
		if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_A)) dir += -1;
		if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_D)) dir += 1;

		neko::vec2 forward = neko::vec2{ 1, 0 };

		m_physicsComponent->applyForce(forward * speed * dir);

		//jump
		bool onGround = (groundCount > 0);
		if (onGround && neko::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE) && !neko::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			neko::vec2 up = neko::vec2{ 0, -1};
			m_physicsComponent->setVelocity(up * jump);
		}

	}

	void Player::onCollisionEnter(Actor* other) {
		if (other->tag == "Ground") groundCount++;
	}

	void Player::onCollisionExit(Actor* other) {
		if (other->tag == "Ground") groundCount--;
	}

	void Player::read(const json_t& value) {
		Actor::read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}
