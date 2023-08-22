#pragma once
#include "Font.h"
#include "Core/Math/Color.h"
#include <string>
#include <memory>

struct SDL_Texture;

namespace neko {
	class Renderer;

	class Text {
	public:
		Text() = default;
		Text(std::shared_ptr<Font> font) : m_font{ font } { }
		~Text();
		void create(Renderer& renderer, const std::string& text, const Color& color);
		void draw(Renderer& renderer, int x, int y);
		void draw(Renderer& renderer, const class Transform& transform);

		friend class Font;
		friend class Renderer;

	private:
		std::shared_ptr<Font> m_font;
		SDL_Texture* m_texture = nullptr;
	};
}