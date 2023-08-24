#include "Boing.h"
#include <vector>
#include <string>

#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"


neko::Highscore highscoreManager;
std::string asteroid;

bool Boing::initialize() {
	// initialize the input system
	neko::g_inputSystem.initialize();

	// create audio
	neko::g_audioSystem.initialize();
	neko::g_audioSystem.addAudio("bgm", "bgm.wav");
	neko::g_audioSystem.addAudio("ui", "ui.wav");
	neko::g_audioSystem.addAudio("damage", "damage.wav");

	m_scene = std::make_unique<neko::Scene>();
	m_scene->load("Scenes\\platformScene.json");
	m_scene->initialize();

	// add events
	EVENT_SUBSCRIBE("AddPoints", Boing::onAddPoints);
	EVENT_SUBSCRIBE("onPlayerDead", Boing::onPlayerDead);

	return true;
}

void Boing::shutdown() {
}

void Boing::update(float dt) {
	int highScore = highscoreManager.readHighScore();

	switch (m_state) {
	case Boing::eState::Title:
		break;

	case Boing::eState::StartGame:
		m_score = 0;
		m_state = eState::StartLevel;
		break;

	case Boing::eState::StartLevel:
		m_scene->removeAll();
		m_score = 0;
		m_state = eState::Game;
		break;

	case Boing::eState::Game:


		break;

	case Boing::eState::PlayerDeadStart:
		m_state = eState::PlayerDead;
		break;

	case Boing::eState::PlayerDead:
			m_score = 0;
			m_state = eState::GameOver;
		break;

	case Boing::eState::GameOver:
		m_scene->removeAll();
		m_state = eState::Title;
		break;

		//default:
			//break;
	}
	m_scene->update(dt);
}

void Boing::draw(neko::Renderer& renderer) {
	m_scene->draw(renderer);
	neko::g_particleSystem.draw(neko::g_renderer);
}

void Boing::onAddPoints(const neko::Event& event) {
	m_score += std::get<int>(event.data);
}

void Boing::onPlayerDead(const neko::Event& event) {
	m_state = eState::PlayerDeadStart;
}
