#include "Enemy.h"
#include "Powerup.h"
#include "Weapon.h"
#include "H_AsteroidField.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Player.h"

namespace neko {
	CLASS_DEFINITION(Powerup);
	bool Powerup::initialize()
	{
		Actor::initialize();

		auto collisionComponent = getComponent<neko::CollisionComponent>();
		if (collisionComponent) {
			auto renderComponent = getComponent<neko::RenderComponent>();
			if (renderComponent) {
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->getRadius() * scale;
			}
		}
		return true;
	}

	void Powerup::update(float dt) {

		Actor::update(dt);

		neko::vec2 forward = neko::vec2{ -1, 0 };
		speed = 75;
		transform.position += forward * speed * neko::g_time.getDeltaTime();
	}

	void Powerup::onCollisionEnter(Actor* other) {

	}

	void Powerup::read(const json_t& value) {
		Actor::read(value);

		READ_DATA(value, speed);
	}
}