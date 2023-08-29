#include "Player.h"
#include "Boing.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Framework.h"


namespace neko {
	CLASS_DEFINITION(Player)

		bool Player::initialize() {
		Actor::initialize();

		// cache off
		m_physicsComponent = getComponent<PhysicsComponent>();
		m_spriteAnimComponent = getComponent<SpriteAnimRenderComponent>();

		return false;
	}

	void Player::update(float dt) {
		Actor::update(dt);

		bool onGround = (groundCount > 0);
		float dir = 0;
		if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_A)) dir += -1;
		if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_D)) dir += 1;

		neko::vec2 forward = neko::vec2{ 1, 0 };

		m_physicsComponent->applyForce(forward * speed * dir * ((onGround) ? 1 : 0.25f));

		//jump
		if (onGround && neko::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE) && !neko::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			neko::vec2 up = neko::vec2{ 0, -1};
			m_physicsComponent->setVelocity(up * jump);
		}

		// animation
		vec2 velocity = m_physicsComponent->m_velocity;
		if (std::fabs(velocity.x) > 0.2f) {
			m_spriteAnimComponent->flipH = (velocity.x < -0.1f);
			m_spriteAnimComponent->setSequence("walk");
		}
		else {
			m_spriteAnimComponent->setSequence("idle");
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
