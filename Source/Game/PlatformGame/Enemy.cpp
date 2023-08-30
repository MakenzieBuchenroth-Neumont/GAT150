#include "Enemy.h"
#include "Boing.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Components/ModelRenderComponent.h"
#include <Framework/Components/PhysicsComponent.h>
#include "Framework/Components/CollisionComponent.h"
#include "Enemy.h"
#include "Player.h"


namespace neko {
	CLASS_DEFINITION(Enemy)

		bool Enemy::initialize() {
		Actor::initialize();

		neko::g_audioSystem.addAudio("maow", "Audio/maow.mp3");

		// cache off
		m_physicsComponent = getComponent<neko::PhysicsComponent>();
		m_spriteAnimComponent = getComponent<neko::SpriteAnimRenderComponent>();

		int r = neko::random(1, 8);


		//if (ran == 1) { // 1 - TOP  2 - LEFT  3 - BOTTOM  4 - RIGHT
			if (r == 1) {
				m_spriteAnimComponent->setSequence("whiteDown");
			}
			else if (r == 2) {
				m_spriteAnimComponent->setSequence("brownDown");
			}
			else if (r == 3) {
				m_spriteAnimComponent->setSequence("grayDown");
			}
			else if (r == 4) {
				m_spriteAnimComponent->setSequence("blackDown");
			}
			else if (r == 5) {
				m_spriteAnimComponent->setSequence("tanDown");
			}
			else if (r == 6) {
				m_spriteAnimComponent->setSequence("siamDown");
			}
			else if (r == 7) {
				m_spriteAnimComponent->setSequence("caliDown");
			}
			else if (r == 8) {
				m_spriteAnimComponent->setSequence("stripeDown");
			}
		//else if (ran == 2) {
			/*if (r == 1) {
				m_spriteAnimComponent->setSequence("whiteRight");
			}
			else if (r == 2) {
				m_spriteAnimComponent->setSequence("brownRight");
			}
			else if (r == 3) {
				m_spriteAnimComponent->setSequence("grayRight");
			}
			else if (r == 4) {
				m_spriteAnimComponent->setSequence("blackRight");
			}
			else if (r == 5) {
				m_spriteAnimComponent->setSequence("tanRight");
			}
			else if (r == 6) {
				m_spriteAnimComponent->setSequence("siamRight");
			}
			else if (r == 7) {
				m_spriteAnimComponent->setSequence("caliRight");
			}
			else if (r == 8) {
				m_spriteAnimComponent->setSequence("stripeRight");
			}
		}
		//else if (ran == 3) {
			if (r == 1) {
				m_spriteAnimComponent->setSequence("whiteUp");
			}
			else if (r == 2) {
				m_spriteAnimComponent->setSequence("brownUp");
			}
			else if (r == 3) {
				m_spriteAnimComponent->setSequence("grayUp");
			}
			else if (r == 4) {
				m_spriteAnimComponent->setSequence("blackUp");
			}
			else if (r == 5) {
				m_spriteAnimComponent->setSequence("tanUp");
			}
			else if (r == 6) {
				m_spriteAnimComponent->setSequence("siamUp");
			}
			else if (r == 7) {
				m_spriteAnimComponent->setSequence("caliUp");
			}
			else if (r == 8) {
				m_spriteAnimComponent->setSequence("stripeUp");
			}
		}
		//else if (ran == 4) {
			if (r == 1) {
				m_spriteAnimComponent->setSequence("whiteLeft");
			}
			else if (r == 2) {
				m_spriteAnimComponent->setSequence("brownLeft");
			}
			else if (r == 3) {
				m_spriteAnimComponent->setSequence("grayLeft");
			}
			else if (r == 4) {
				m_spriteAnimComponent->setSequence("blackLeft");
			}
			else if (r == 5) {
				m_spriteAnimComponent->setSequence("tanLeft");
			}
			else if (r == 6) {
				m_spriteAnimComponent->setSequence("siamLeft");
			}
			else if (r == 7) {
				m_spriteAnimComponent->setSequence("caliLeft");
			}
			else if (r == 8) {
				m_spriteAnimComponent->setSequence("stripeLeft");
			}
		}*/

		return false;
	}

	void Enemy::update(float dt) {
		Actor::update(dt);

		neko::vec2 forward = neko::vec2{ 0, -1 }.rotate(transform.rotation);
		Player* player = m_scene->getActor<Player>();
		if (player)
		{
			neko::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->applyForce(direction.normalized() * speed);
		}

	}

	void Enemy::onCollisionEnter(Actor* other) {
		if (other->tag == "Bark") {
			neko::g_audioSystem.playOneShot("maow");
			neko::EventManager::Instance().dispatchEvent("onEnemyDead", 0);
		}
	}

	void Enemy::onCollisionExit(Actor* other) {
	}

	void Enemy::read(const json_t& value) {
		Actor::read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}
