#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace neko {
	class SpriteComponent : public RenderComponent {
	public:
		CLASS_DECLARATION(SpriteComponent)

		void update(float dt) override;
		void draw(class Renderer& renderer) override;

		virtual float getRadius() { return m_texture->getSize().length() * 0.5f; }
		
	public:
		res_t<Texture> m_texture;
	};
}