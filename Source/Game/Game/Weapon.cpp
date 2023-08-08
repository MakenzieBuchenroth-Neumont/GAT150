#include "Weapon.h"
#include "Renderer/Renderer.h"

void Weapon::update(float dt) {
	Actor::update(dt);

	neko::vec2 forward = neko::vec2{ 0, -1 }.rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * neko::g_time.getDeltaTime();
	//m_transform.position.x = neko::wrap(m_transform.position.x, neko::g_renderer.getWidth());
	//m_transform.position.y = neko::wrap(m_transform.position.y, neko::g_renderer.getHeight());

	if (m_transform.position.x >= neko::g_renderer.getWidth() || m_transform.position.x <= 0 ) {
		m_destroyed = true;
	}
	if (m_transform.position.y >= neko::g_renderer.getHeight() || m_transform.position.y <= 0) {
		m_destroyed = true;
	}
}

void Weapon::onCollision(Actor* other) {
	if (other->m_tag != m_tag) {
		m_destroyed = true;
	}
}
