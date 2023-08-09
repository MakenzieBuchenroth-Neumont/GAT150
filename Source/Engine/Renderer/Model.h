#pragma once
#include "Core/Core.h"
#include "Framework/Resource/Resource.h"
#include <vector>

namespace neko {
	class Renderer;

	class Model : public Resource {
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {};

		virtual bool create(std::string filename, ...) override;
		bool load(const std::string& filename);

		void draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void draw(Renderer& renderer, const Transform transform);

		float getRadius();

	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;
	};
}