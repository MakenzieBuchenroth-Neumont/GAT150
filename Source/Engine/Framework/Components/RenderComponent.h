#pragma once
#include "Component.h"

namespace neko {
	class RenderComponent : public Component {
	public:
		virtual void draw(class Renderer& renderer) = 0;
		virtual float getRadius() { return 0; }
	};
}