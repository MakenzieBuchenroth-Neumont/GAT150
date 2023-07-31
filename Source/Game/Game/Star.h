#pragma once
#include "Core/Vector2.h"
#include "Renderer/Renderer.h"

namespace neko {
class Star {
	public:
		Star(neko::Vector2& pos, neko::Vector2& vel) : m_pos{ pos }, m_vel{ vel } {}

		inline void update(int width, int height) {
			m_pos += m_vel;
			if (m_pos.x >= width) m_pos.x = 0;
			if (m_pos.y >= width) m_pos.y = 0;
		}

		inline void draw(neko::Renderer& renderer) {
			renderer.drawPoint(m_pos.x, m_pos.y);
		}

	public:
		neko::Vector2 m_pos;
		neko::Vector2 m_vel;
	};
}