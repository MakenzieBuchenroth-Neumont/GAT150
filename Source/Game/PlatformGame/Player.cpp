#include "Player.h"
#include "Boing.h"
#include "Weapon.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"


namespace neko {
	CLASS_DEFINITION(Player)

		bool Player::initialize() {
		Actor::initialize();

		// cache off
		m_physicsComponent = getComponent<PhysicsComponent>();
		m_spriteAnimComponent = getComponent<SpriteAnimRenderComponent>();
		neko::g_audioSystem.addAudio("bark", "Audio/bork.mp3");

		return false;
	}

	void Player::update(float dt) {
		Actor::update(dt);

		vec2 dir = { 0, 0 };
		vec2 velocity = m_physicsComponent->m_velocity;

			if (neko::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_A) && !neko::g_inputSystem.getKeyDown(SDL_SCANCODE_A)) {
				m_spriteAnimComponent->setSequence("idleLeft");
			}
			if (neko::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_D) && !neko::g_inputSystem.getKeyDown(SDL_SCANCODE_D)) {
				m_spriteAnimComponent->setSequence("idleRight");
			}
			if (neko::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_W) && !neko::g_inputSystem.getKeyDown(SDL_SCANCODE_W)) {
			
				m_spriteAnimComponent->setSequence("idleUp");
			}
			if (neko::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_S) && !neko::g_inputSystem.getKeyDown(SDL_SCANCODE_S)) {
				m_spriteAnimComponent->setSequence("idleDown");
			}
			if (neko::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_SPACE) && !neko::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE)) {
				m_spriteAnimComponent->setSequence("idleUp");
			}

			if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_A)) { 
				dir += { -1, 0};
				m_spriteAnimComponent->setSequence("walkLeft");
			}
			else if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_D)) { 
				dir += { 1, 0};
				m_spriteAnimComponent->setSequence("walkRight");
			}
			else if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_W)) {
				dir += { 0, -1};
				m_spriteAnimComponent->setSequence("walkUp");
			}
			else if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_S)) {
				dir += { 0,1};
				m_spriteAnimComponent->setSequence("walkDown");
			}

			neko::vec2 forward = neko::vec2{ 1, 1 };
			m_physicsComponent->applyForce(dir * speed * forward);

		// fire weapon
			if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE) && !neko::g_inputSystem.getPreviousKeyDown(SDL_SCANCODE_SPACE)) {
				auto weapon = INSTANTIATE(Weapon, "Bark");
				weapon->transform.position = forward * transform.position.y;
				weapon->transform.rotation = neko::pi;
				weapon->initialize();
				m_scene->add(std::move(weapon));
				neko::g_audioSystem.playOneShot("bark");
				m_spriteAnimComponent->setSequence("bork");
			}
	}

	void Player::onCollisionEnter(Actor* other) {
		if (other->tag == "Enemy") {
			neko::EventManager::Instance().dispatchEvent("onPlayerDead", 0);
		}
	}

	void Player::onCollisionExit(Actor* other) {
	}

	void Player::read(const json_t& value) {
		Actor::read(value);

		READ_DATA(value, speed);
	}
}
