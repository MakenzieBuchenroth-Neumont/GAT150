#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Framework/Event/EventManager.h"
#include <iostream>
#include <fstream>
#include <vector>

class Boing : public neko::Game, neko::IEventListener {

public:
	enum class eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOver
	};

public:
	// Inherited via Game
	virtual bool initialize() override;
	virtual void shutdown() override;

	virtual void update(float dt) override;
	virtual void draw(neko::Renderer& renderer) override;

	void setState(eState state) { m_state = state; }
	void onAddPoints(const neko::Event& event);
	void onPlayerDead(const neko::Event& event);
	void onEnemyDead(const neko::Event& event);

	int m_highScore = 0;
	bool m_powerup = false;
private:
	eState m_state = eState::Title;

	float m_spawnTimer = 0;
	float m_spawnTime = 4;
	float m_stateTimer = 0;

	float m_powerupTimer = 32;
	float m_powerDuration = 5;

	float m_pointTimer = 0;
};