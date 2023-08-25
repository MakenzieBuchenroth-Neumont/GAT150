#pragma once
#include "Framework/Components/RenderComponent.h"
#include "Renderer/Text.h"

namespace neko {
	class TextRenderComponent : public RenderComponent {
	public:
		CLASS_DECLARATION(TextRenderComponent)
		TextRenderComponent() = default;
		TextRenderComponent(const TextRenderComponent& other);
		bool initialize() override;
		void update(float dt) override;
		void draw(class Renderer& renderer) override;
		void setText(const std::string& string);
	public:
		std::string text;
		std::string fontName;
		int fontSize = 0;
		Color color;
	private:
		bool m_changed = true;
		std::unique_ptr<Text> m_text;
	};
}
