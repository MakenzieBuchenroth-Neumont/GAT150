#include "Boing.h"
#include "Enemy.h"
#include <vector>
#include <string>

#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include <Framework/Components/SpriteAnimRenderComponent.h>


neko::Highscore highscoreManager;
int enemyTimer = 700;

bool Boing::initialize() {
	// initialize the input system
	neko::g_inputSystem.initialize();

	// create audio
	neko::g_audioSystem.initialize();
	//neko::g_audioSystem.addAudio("bgm", "Audio/bgm.mp3");

	m_scene = std::make_unique<neko::Scene>();
	m_scene->load("Scenes/platformScene.json");
	m_scene->initialize();

	// add events
	EVENT_SUBSCRIBE("AddPoints", Boing::onAddPoints);
	EVENT_SUBSCRIBE("onPlayerDead", Boing::onPlayerDead);
	EVENT_SUBSCRIBE("onEnemyDead", Boing::onEnemyDead);

	return true;
}

void Boing::shutdown() {
}

void Boing::update(float dt) {
	int highScore = highscoreManager.readHighScore();
	m_scene->getActorByName("HiScore")->getComponent<neko::TextRenderComponent>()->setText("HIGH SCORE: " + std::to_string(highscoreManager.readHighScore()));

	switch (m_state) {
	case Boing::eState::Title:
		//neko::g_audioSystem.playOneShot("bgm", true);
		m_scene->getActorByName("Player")->active = false;
		m_scene->getActorByName("Title")->active = true;
		m_scene->getActorByName("Subtitle")->active = true;
		if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_RETURN)) {
			m_state = eState::StartGame;
		}
		break;

	case Boing::eState::StartGame:
		m_score = 0;
		{
			auto player_sprite = m_scene->getActorByName("Player")->getComponent<neko::SpriteAnimRenderComponent>();
			player_sprite->setSequence("idleUp");
		}
		m_scene->getActorByName("Title")->active = false;
		m_scene->getActorByName("Subtitle")->active = false;
		m_scene->getActorByName("Player")->active = true;
		m_state = eState::StartLevel;
		break;

	case Boing::eState::StartLevel:
		m_scene->removeAll();
		m_score = 0;
		m_state = eState::Game;
		break;

	case Boing::eState::Game:
		enemyTimer -= dt;
	if (enemyTimer == 0) {
		auto enemy = INSTANTIATE(Enemy, "Enemy")

		int ran = neko::random(1, 4);

		if (ran == 1) {
			enemy->transform.position = { neko::random(0, neko::g_renderer.getWidth()), 0 };
		}
		else if (ran == 2) {
			enemy->transform.position = { neko::random(neko::g_renderer.getHeight(), 0), 0 };
		}
		else if (ran == 3) {
			enemy->transform.position = { neko::random(neko::g_renderer.getHeight(), neko::g_renderer.getWidth()), 0 };
		}
		else if (ran == 4) {
			enemy->transform.position = { neko::random(neko::g_renderer.getWidth(), neko::g_renderer.getWidth()), 0 };
		}

		enemy->initialize();
		m_scene->add(std::move(enemy));
		enemyTimer = 700;
		}

		break;

	case Boing::eState::PlayerDeadStart:
		m_state = eState::PlayerDead;
		break;

	case Boing::eState::PlayerDead:
			if (m_stateTimer <= 0) {
				m_scene->removeAll();

				if (m_score > highscoreManager.readHighScore()) {
					highscoreManager.saveHighScore(m_score);
				}
				m_score = 0;
				m_state = eState::GameOver;
			}
			else {
				m_stateTimer -= dt;
			}

			//neko::g_audioSystem.stopSound("bgm");
			m_state = eState::GameOver;
		break;

	case Boing::eState::GameOver:
		m_scene->removeAll();
		m_state = eState::Title;
		break;

		//default:
			//break;
	}

	m_scene->getActorByName("Score")->getComponent<neko::TextRenderComponent>()->setText("SCORE:" + std::to_string(m_score));
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

void Boing::onEnemyDead(const neko::Event& event) {
	neko::EventManager::Instance().dispatchEvent("AddPoints", 1);
	m_scene->getActorByName("Enemy")->destroyed = true;

}
