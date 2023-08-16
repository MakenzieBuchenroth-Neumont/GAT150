#pragma once
#include "Framework/Actor.h"

class Powerup : public neko::Actor {
public:
	Powerup(float speed, const neko::Transform& transform) :
		neko::Actor{ transform },
		speed{ speed }
	{}

	bool initialize() override;
	void update(float dt) override;
	void onCollision(Actor* other) override;

	bool destroyed = false;

private:
	float speed = 0;
};