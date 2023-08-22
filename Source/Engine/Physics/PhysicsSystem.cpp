#include "PhysicsSystem.h"

namespace neko {
	bool PhysicsSystem::initialize()
	{
		b2Vec2 gravity{ 0, 10 };
		m_world = std::make_unique<b2World>(gravity);
		return true;
	}
	void PhysicsSystem::update(float dt)
	{
		//
	}
}