#pragma once
#include "Core/Vector2.h"
#include "Framework/Resoure/Resource.h"

struct SDL_Texture;

namespace neko {
	class Texture : public Resource {
	public:
		Texture() = default;
		~Texture();

		bool load(std::string filename, class Renderer& renderer);
		vec2 getSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture = nullptr;

		// Inherited via Resource
		virtual bool create(std::string& filename, ...) override;
	};
}