#pragma once
#include "Framework/Components/Component.h"
#include "Core/Json.h"
#include <Framework/Actor.h>

class EnemyComponent : public neko::Component {
public:
	/*
	Enemy(float speed, float turnRate, const neko::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;
	}*/
	bool initialize() override;
	void update(float dt) override;
	void onCollision(neko::Actor* other);
	void read(const neko::json_t& value);

private:
	float speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
	float m_health = 10;
};