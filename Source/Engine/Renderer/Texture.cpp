#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include "SDL2-2.28.0/include/SDL_image.h"

namespace neko {
	Texture::~Texture() {
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	bool Texture::create(std::string filename, ...) {
		va_list args;

		va_start(args, filename);
		Renderer& renderer = va_arg(args, Renderer);
		va_end(args);

		return load(filename, renderer);
	}

	bool Texture::load(std::string filename, Renderer& renderer) {
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface) {
			WARNING_LOG("Checking for texture");
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture) {
			WARNING_LOG("Couldn't load image");
			return false;
		}

		return true;
	}

	vec2 Texture::getSize() {
		//ASSERT_LOG(m_texture != nullptr, "No texture found.");
		SDL_Point point;
		// https://wiki.libsdl.org/SDL2/SDL_QueryTexture
		SDL_QueryTexture(m_texture, NULL, NULL, &point.x, &point.y);

		return vec2{ point.x, point.y };
	}
}