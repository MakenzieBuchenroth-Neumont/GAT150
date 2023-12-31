#include "Box2DPhysicsComponent.h"
#include "Framework/Actor.h"

namespace neko {
	CLASS_DEFINITION(Box2DPhysicsComponent)

	bool Box2DPhysicsComponent::initialize() {
		m_body = PhysicsSystem::Instance().createBody(m_owner->transform.position, m_owner->transform.rotation, data);
		m_body->SetGravityScale(data.gravityScale);
		m_body->SetLinearDamping(data.damping);
		m_body->SetAngularDamping(data.angularDamping);

		return true;
	}

	void Box2DPhysicsComponent::onDestroy() {
		if (m_body) {
			m_body->SetEnabled(false);
			PhysicsSystem::Instance().destroyBody(m_body);
		}
	}

	void Box2DPhysicsComponent::update(float dt) {
		Vector2 position = B2VEC2_TO_VEC2(m_body->GetPosition());
		m_owner->transform.position = PhysicsSystem::Instance().worldToScreen(position);
		m_owner->transform.rotation = m_body->GetAngle();
		m_velocity = B2VEC2_TO_VEC2(m_body->GetLinearVelocity());
	}

	void Box2DPhysicsComponent::applyForce(const vec2& force) {
		m_body->ApplyForceToCenter(VEC2_TO_B2VEC2(force), true);
	}

	void Box2DPhysicsComponent::applyTorque(float torque) {
		m_body->ApplyTorque(torque, true);
	}

	void Box2DPhysicsComponent::setVelocity(const vec2& m_velocity) {
		m_body->SetLinearVelocity(VEC2_TO_B2VEC2(m_velocity));
	}

	void Box2DPhysicsComponent::read(const json_t& value) {
		READ_NAME_DATA(value, "damping", data.damping);
		READ_NAME_DATA(value, "angularDamping", data.angularDamping);
		READ_NAME_DATA(value, "gravityScale", data.gravityScale);
		READ_NAME_DATA(value, "constrainAngle", data.constrainAngle);
		READ_NAME_DATA(value, "isDynamic", data.isDynamic);
	}
}