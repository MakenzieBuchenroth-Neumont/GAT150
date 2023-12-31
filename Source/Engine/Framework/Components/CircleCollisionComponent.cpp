#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace neko {
    CLASS_DEFINITION(CircleCollisionComponent)

    void CircleCollisionComponent::update(float dt) {

    }

    bool CircleCollisionComponent::checkCollision(CollisionComponent* collision) {
        float distance = m_owner->transform.position.distance(collision->m_owner->transform.position);
        float radius = m_radius + collision->m_radius;

        return (distance <= radius);
    }

    void CircleCollisionComponent::read(const json_t& value) {
        //
    }
}
