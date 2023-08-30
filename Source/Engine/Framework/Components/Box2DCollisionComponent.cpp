#include "Box2DCollisionComponent.h"
#include "Box2DPhysicsComponent.h"
#include "Framework/Actor.h"
#include "SpriteComponent.h"

namespace neko {
	CLASS_DEFINITION(Box2DCollisionComponent)

		bool Box2DCollisionComponent::initialize() {
		auto component = m_owner->getComponent<Box2DPhysicsComponent>();
		if (component) {
			auto spriteComponent = m_owner->getComponent<SpriteComponent>();
			if (spriteComponent) {
				if (data.size.x == 0 && data.size.y == 0) {
					data.size = vec2{ spriteComponent->source.w, spriteComponent->source.h };
				}
				data.offset = spriteComponent->origin - vec2{ 0.5f, 0.5f };
			}

			data.size = data.size * scaleOffset * m_owner->transform.scale;

			if (component->m_body->GetType() == b2_staticBody) {
				PhysicsSystem::Instance().setCollisionBoxStatic(component->m_body, data, m_owner);
			}
			else {
				PhysicsSystem::Instance().setCollisionBox(component->m_body, data, m_owner);
			}
		}

		return true;
	}

	void Box2DCollisionComponent::update(float dt) {
	}

	void Box2DCollisionComponent::read(const json_t& value) {
		READ_NAME_DATA(value, "size", data.size);
		READ_NAME_DATA(value, "density", data.density);
		READ_NAME_DATA(value, "friction", data.friction);
		READ_NAME_DATA(value, "restitution", data.restitution);
		READ_NAME_DATA(value, "isTrigger", data.isTrigger);

		READ_DATA(value, scaleOffset);
	}
}