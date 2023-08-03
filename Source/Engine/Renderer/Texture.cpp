#include "Texture.h"
#include "Renderer.h"
#include "SDL2-2.28.0/include/SDL_image.h"

namespace neko {
	Texture::~Texture() {
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	bool Texture::create(Renderer& renderer, const std::string& filename) {
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface) {
			// LOG WARNING
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture) {
			return false;
		}

		return true;
	}

	vec2 Texture::getSize() {
		// ASSERT texture is not null
		SDL_Point point;
		// https://wiki.libsdl.org/SDL2/SDL_QueryTexture
		SDL_QueryTexture(m_texture, NULL, &point.x, &point.y, NULL);

		return vec2{ point.x, point.y };
	}
}