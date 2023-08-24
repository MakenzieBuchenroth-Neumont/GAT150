#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

class b2Body;

namespace neko {
	class Box2DPhysicsComponent : public PhysicsComponent {
	public:
		CLASS_DECLARATION(Box2DPhysicsComponent)

		bool initialize() override;
		void onDestroy() override;

		void update(float dt) override;
		virtual void applyForce(const vec2& force) override;
		virtual void applyTorque(float torque) override;
		virtual void setVelocity(const vec2& m_velocity) override;

		friend class Box2DCollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body = nullptr;
	};
}