#pragma once
#include "Core/Core.h"

namespace neko {
	struct ParticleData {
		vec2 position;
		vec2 prevPosition;
		vec2 velocity;
		float damping = 0;
		Color color;
		float lifetimer = 0;
		float lifetime = 0;
	};

	class Particle {
	public:
		Particle() = default;
		void initialize(const ParticleData& data)
		{
			m_data = data;
			m_isActive = true;
		}
		void update(float dt);
		void draw(class Renderer& renderer);

		friend class ParticleSystem;

	private:
		ParticleData m_data;
		bool m_isActive = false;
	};
}