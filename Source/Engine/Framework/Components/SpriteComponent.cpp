#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace neko {
	CLASS_DEFINITION(SpriteComponent)

	bool SpriteComponent::initialize() {

		if (!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_renderer);
		if (source.w == 0 && source.h == 0) {
			if (m_texture) {
				source.x = 0;
				source.y = 0;
				source.w = (int)m_texture->getSize().x;
				source.h = (int)m_texture->getSize().y;
			}
		}

		return true;
	}

	void SpriteComponent::update(float dt) {
		//
	}

	void SpriteComponent::draw(Renderer& renderer) {
		renderer.drawTexture(m_texture.get(), source, m_owner->transform, origin, flipH);
	}

	void SpriteComponent::read(const json_t& value) {
		READ_DATA(value, textureName);
		READ_DATA(value, source);
		READ_DATA(value, flipH);
		READ_DATA(value, origin);
	}
}
