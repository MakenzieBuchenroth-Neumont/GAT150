#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace neko {
	void SpriteComponent::update(float dt) {

	}

	void SpriteComponent::draw(Renderer& renderer) {
		renderer.drawTexture(m_texture.get(), m_owner->m_transform);
	}
}
