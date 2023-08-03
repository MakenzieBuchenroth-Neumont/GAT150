#pragma once
#include "Core/Vector2.h"
#include <SDL2-2.28.0/include/SDL_render.h>

struct SLD_Texture;

namespace neko {
	class Texture {
	public:
		Texture() = default;
		~Texture();

		bool create(class Renderer& renderer, const std::string& filename);
		vec2 getSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture = nullptr;
	};
}