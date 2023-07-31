#pragma once
#include "Renderer.h"
#include "Font.h"
#include "Core/Color.h"
#include <string>
#include <memory>

namespace neko {
	class Text {
	public:
		Text() = default;
		Text(std::shared_ptr<Font> font) : m_font{ font } { }
		~Text();
		void create(Renderer& renderer, const std::string& text, const Color& color);
		void draw(Renderer& renderer, int x, int y);

		friend class Font;
		friend class Renderer;

	private:
		std::shared_ptr<Font> m_font;
		struct SDL_Texture* m_texture = nullptr;
	};
}