#pragma once
#include "Framework/Actor.h"

class Weapon : public neko::Actor {
public:
	Weapon(float speed, const neko::Transform& transform) :
		neko::Actor{ transform },
		m_speed{ speed }
	{ lifespan = 2.0f; }
	void update(float dt) override;
	void onCollision(Actor* other) override;

private:
	float m_speed = 0;
};