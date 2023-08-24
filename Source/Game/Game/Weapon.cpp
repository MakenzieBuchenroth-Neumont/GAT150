#include "Weapon.h"
#include "Renderer/Renderer.h"

void Weapon::update(float dt) {
	Actor::update(dt);

	neko::vec2 forward = neko::vec2{ 0, -1 }.rotate(transform.rotation);
	transform.position += forward * m_speed * neko::g_time.getDeltaTime();
	//m_transform.position.x = neko::wrap(m_transform.position.x, neko::g_renderer.getWidth());
	//m_transform.position.y = neko::wrap(m_transform.position.y, neko::g_renderer.getHeight());

	if (transform.position.x >= neko::g_renderer.getWidth() || transform.position.x <= 0 ) {
		destroyed = true;
	}
	if (transform.position.y >= neko::g_renderer.getHeight() || transform.position.y <= 0) {
		destroyed = true;
	}
}

void Weapon::onCollisionEnter(Actor* other) {
	if (other->tag != tag) {
		destroyed = true;
	}
}
