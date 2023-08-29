#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace neko {
	class SpriteComponent : public RenderComponent {
	public:
		CLASS_DECLARATION(SpriteComponent)

		bool initialize() override;
		void update(float dt) override;
		void draw(class Renderer& renderer) override;
		
	public:
		Rect source;
		bool flipH = false;
		vec2 origin{ 0.5f, 0.5f };
		std::string textureName;
		res_t<Texture> m_texture;
	};
}