#pragma once
#include "Framework/Components/Component.h"

namespace neko {
	class CollisionComponent : public Component {
	public:
		virtual bool checkCollision(CollisionComponent* collision) { return true; }

	public:
		float m_radius = 0;

	};
}