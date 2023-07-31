#pragma once
#include "Framework/Actor.h"

class Powerup : public neko::Actor {
public:
	Powerup(float speed, const neko::Transform& transform, std::shared_ptr<neko::Model> model) :
		neko::Actor{ transform, model },
		m_speed{ speed }
	{}

	void update(float dt) override;
	void onCollision(Actor* other) override;

	bool m_destroyed = false;

private:
	float m_speed = 0;
};