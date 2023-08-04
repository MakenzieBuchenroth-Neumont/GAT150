#pragma once
#include "Core/Vector2.h"
#include "Framework/Resource/Resource.h"

struct SDL_Texture;

namespace neko {
	class Texture : public Resource {
	public:
		Texture() = default;
		~Texture();

		virtual bool create(std::string filename, ...) override;

		bool load(std::string filename, class Renderer& renderer);
		vec2 getSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture = nullptr;
	};
}