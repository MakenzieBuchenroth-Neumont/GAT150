#pragma once
#include "CollisionComponent.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

namespace neko {
	class Box2DCollisionComponent : public CollisionComponent {
	public:
		using collisionFunction = std::function<void(Actor*)>;

	public:
		CLASS_DECLARATION(Box2DCollisionComponent)

		virtual bool initialize() override;
		virtual void update(float dt) override;

	private:
		PhysicsSystem::CollisionData data;
		vec2 scaleOffset = vec2{ 1, 1 };
	};
}