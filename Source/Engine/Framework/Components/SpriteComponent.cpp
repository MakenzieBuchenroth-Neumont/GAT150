#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace neko {
	CLASS_DEFINITION(SpriteComponent)

	bool SpriteComponent::initialize() {
		if (!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		return true;
	}

	void SpriteComponent::update(float dt) {

	}

	void SpriteComponent::draw(Renderer& renderer) {
		renderer.drawTexture(m_texture.get(), m_owner->transform);
	}

	void SpriteComponent::read(const json_t& value) {
		READ_DATA(value, textureName);
	}
}
