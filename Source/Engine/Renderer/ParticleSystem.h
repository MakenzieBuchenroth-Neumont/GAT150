#pragma once
#include "Particle.h"

namespace neko {
	class ParticleSystem {
	public:
		ParticleSystem() = default;
		ParticleSystem(int maxCount)
		{
			m_particles.resize(maxCount);
		}
		void update(float dt);
		void draw(class Renderer& renderer);
		Particle* getFreeParticle();
	private:
		std::vector<Particle> m_particles;
	};

	extern ParticleSystem g_particleSystem;
};