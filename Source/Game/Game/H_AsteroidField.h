#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Star.h"
#include <iostream>
#include <fstream>
#include <vector>

class H_AsteroidField : public neko::Game {

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


	std::vector<neko::Star> stars;
	std::shared_ptr<neko::Font> m_font;
	std::unique_ptr<neko::Text> m_scoreText;
	std::unique_ptr<neko::Text> m_highScoreText;
	std::unique_ptr<neko::Text> m_titleText;
	std::unique_ptr<neko::Text> m_subTitleText;
	std::unique_ptr<neko::Text> m_endText;
};