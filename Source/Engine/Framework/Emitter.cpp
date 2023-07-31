#include "Emitter.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"

namespace neko {

	void neko::Emitter::update(float dt) {
		Actor::update(dt);
		// create burst particles
		if (m_data.burst)
		{
			m_data.burst = false;
			for (int i = 0; i < m_data.burstCount; i++)
			{
				emit();
			}
		}
		// create particles based on rate
		if (m_data.spawnRate > 0.0f)
		{
			m_data.spawnRateTimer += dt;
			while (m_data.spawnRateTimer > 0)
			{
				emit();
				m_data.spawnRateTimer -= (1 / m_data.spawnRate);
			}
		}
	}

	void neko::Emitter::draw(neko::Renderer& renderer) {
		//
	}

	void neko::Emitter::emit() {
		Particle* particle = g_particleSystem.getFreeParticle();
		if (particle)
		{
			ParticleData data;
			data.lifetime = randomf(m_data.lifetimeMin, m_data.lifetimeMax);
			data.lifetimer = 0.0f;
			data.position = m_transform.position;
			data.prevPosition = data.position;
			data.color = m_data.color;
			float angle = m_transform.rotation + m_data.angle + randomf(-m_data.angleRange, m_data.angleRange);
			vec2 direction = vec2{ 0, -1 }.rotate(angle);
			data.velocity = direction * randomf(m_data.speedMin, m_data.speedMax);
			data.damping = m_data.damping;
			particle->initialize(data);
		}
	}
};
