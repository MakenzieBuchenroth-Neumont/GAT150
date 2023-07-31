#pragma once
#include "Framework/Actor.h"

class Weapon : public neko::Actor {
public:
	Weapon(float speed, const neko::Transform& transform, std::shared_ptr<neko::Model> model) :
		neko::Actor{ transform, model },
		m_speed{ speed }
	{ m_lifespan = 2.0f; }
	void update(float dt) override;
	void onCollision(Actor* other) override;

private:
	float m_speed = 0;
};