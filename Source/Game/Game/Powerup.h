#pragma once
#include "Framework/Actor.h"

namespace neko {
	class Powerup : public neko::Actor {
	public:
	CLASS_DECLARATION(Powerup);
		Powerup() = default;
		//Powerup(float speed, const neko::Transform& transform) :
			//neko::Actor{ transform },
			//speed{ speed }
		//{}

		bool initialize() override;
		void update(float dt) override;
		void onCollisionEnter(Actor* other) override;

		bool destroyed = false;

	private:
		float speed = 0;
	};
}