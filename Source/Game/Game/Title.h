#pragma once
#include "Framework/Actor.h"

namespace neko {
	class Title : public neko::Actor {
	public:
		CLASS_DECLARATION(Title);
		Title() = default;
		Title(const neko::Transform& transform) :
			neko::Actor{ transform }
		{}
		void update(float dt) override;

	private:
	};
}