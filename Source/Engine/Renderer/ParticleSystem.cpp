#include "ParticleSystem.h"

namespace neko {
    ParticleSystem g_particleSystem(1000);

    void ParticleSystem::update(float dt) {


        for (auto& particle : m_particles)
        {
            if (particle.m_isActive) particle.update(dt);
        }
    }

    void ParticleSystem::draw(Renderer& renderer) {
        for (auto& particle : m_particles)
        {
            if (particle.m_isActive) particle.draw(renderer);
        }
    }

    Particle* ParticleSystem::getFreeParticle() {
        for (auto& particle : m_particles)
        {
            if (!particle.m_isActive) return &particle;
        }
        return nullptr;
    }
};
