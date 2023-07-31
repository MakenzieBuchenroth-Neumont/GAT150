#pragma once
#include "Framework/Actor.h"

class Player : public neko::Actor {
public:
	Player(float speed, float turnRate, const neko::Transform& transform, std::shared_ptr<neko::Model> model) :
		neko::Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}
	void update(float dt) override;
	void onCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 100;
	bool dead = false;
};