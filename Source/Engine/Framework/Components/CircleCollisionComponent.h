#pragma once
#include "Framework/Components/CollisionComponent.h"

namespace neko {
	class CircleCollisionComponent : public CollisionComponent {
	public:
		CLASS_DECLARATION(CircleCollisionComponent)

		// Inherited via CollisionComponent
		virtual void update(float dt) override;

		virtual bool checkCollision(CollisionComponent* collision) override;

	};
}
