#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace neko
{
	CLASS_DEFINITION(Weapon);

	bool Weapon::initialize()
	{
		Actor::initialize();

		m_physicsComponent = getComponent<neko::PhysicsComponent>();
		m_spriteAnimComponent = getComponent<neko::SpriteAnimRenderComponent>();

		lifespan = 0.5f;

		return false;
	}

	void Weapon::onDestroy()
	{
		Actor::onDestroy();
	}

	void Weapon::update(float dt)
	{
		Actor::update(dt);
		
		neko::vec2 forward = neko::vec2{ 0, -1 }.rotate(transform.rotation);
		m_physicsComponent->setVelocity(forward * speed);

		//transform.position.x = neko::wrap(transform.position.x, (float)neko::g_renderer.getWidth());
		//transform.position.y = neko::wrap(transform.position.y, (float)neko::g_renderer.getHeight());
	}

	void Weapon::onCollisionEnter(neko::Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
		}
	}

	void Weapon::read(const json_t& value)
	{
		Actor::read(value);

		READ_DATA(value, speed);
		READ_DATA(value, tag);
	}
}