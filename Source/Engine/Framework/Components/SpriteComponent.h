#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

namespace neko {
	class SpriteComponent : public RenderComponent {
	public:
		void update(float dt) override;
		void draw(class Renderer& renderer) override;

	public:
		res_t<Texture> m_texture;
	};
}