#pragma once
#include "Framework/Components/Component.h"

namespace neko {
	class CollisionComponent : public Component {
	public:
		virtual bool checkCollision(CollisionComponent* collision) = 0;

	public:
		float m_radius = 0;

	};
}