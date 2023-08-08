#include "H_AsteroidField.h"
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

#include "Title.h"
#include "Powerup.h"


neko::Highscore highscoreManager;
std::string asteroid;

bool H_AsteroidField::initialize() {
	// initialize the input system
	neko::g_inputSystem.initialize();

	// create font

	m_scoreText = std::make_unique<neko::Text>(neko::g_resourceManager.get<neko::Font>("font.ttf", 28));
	m_scoreText->create(neko::g_renderer, "SCORE 000000", neko::Color(1, 1, 1, 1));

	m_highScoreText = std::make_unique<neko::Text>(neko::g_resourceManager.get<neko::Font>("font.ttf", 28));
	
	m_titleText = std::make_unique<neko::Text>(neko::g_resourceManager.get<neko::Font>("font.ttf", 28));
	m_titleText->create(neko::g_renderer, "HOTH ASTEROID FIELD", neko::Color(1, 1, 1, 1));

	m_subTitleText = std::make_unique<neko::Text>(neko::g_resourceManager.get<neko::Font>("font.ttf", 28));
	m_subTitleText->create(neko::g_renderer, "PRESS SPACE TO PLAY", neko::Color(1, 1, 1, 1));

	m_endText = std::make_unique<neko::Text>(neko::g_resourceManager.get<neko::Font>("font.ttf", 28));
	m_endText->create(neko::g_renderer, "YOU GOT CAUGHT! PRESS SPACE TO PLAY AGAIN", neko::Color(1, 1, 1, 1));

	// create audio
	neko::g_audioSystem.initialize();
	neko::g_audioSystem.addAudio("bgm", "bgm.wav");
	neko::g_audioSystem.addAudio("ui", "ui.wav");
	neko::g_audioSystem.addAudio("damage", "damage.wav");

	for (int i = 0; i < 100; i++) {
		neko::Vector2 pos(neko::Vector2((neko::random(neko::g_renderer.getWidth())), neko::random(neko::g_renderer.getHeight())));
		neko::Vector2 vel(neko::randomf(1, 4), 0.0f);

		stars.push_back(neko::Star(pos, vel));
	}

	m_scene = std::make_unique<neko::Scene>();

	return true;
}

void H_AsteroidField::shutdown() {
}

void H_AsteroidField::update(float dt) {
	int highScore = highscoreManager.readHighScore();
	m_highScoreText->create(neko::g_renderer, "HIGH SCORE " + std::to_string(highscoreManager.readHighScore()), neko::Color(1, 1, 1, 1));

	switch (m_state) {
	case H_AsteroidField::eState::Title:
		if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
			neko::g_audioSystem.playOneShot("ui");
		}
		break;

	case H_AsteroidField::eState::StartGame:
		m_powerup = false;
		m_pointTimer = 0;
		m_powerupTimer = 32;
		neko::g_audioSystem.playOneShot("bgm", true);
		m_score = 0;
		m_state = eState::StartLevel;
		break;

	case H_AsteroidField::eState::StartLevel:
		m_scene->removeAll();
		m_score = 0;
	{
			// create player
		std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, 0, neko::Transform{ {100.0f, 300.0f }, 0, 6});
		player->m_tag = "Player";
		player->m_game = this;
		//create components
		// sprite
		std::unique_ptr<neko::SpriteComponent> component = std::make_unique<neko::SpriteComponent>();
		component->m_texture = neko::g_resourceManager.get<neko::Texture>("falcon.png", neko::g_renderer);
		player->addComponent(std::move(component));
		// physics
		auto physicsComponent = std::make_unique<neko::EnginePhysicsComponent>();
		player->addComponent(std::move(physicsComponent));

		m_scene->add(std::move(player));
	}
		m_state = eState::Game;
		break;

	case H_AsteroidField::eState::Game:
		m_spawnTimer += dt;
		m_powerupTimer -= dt;
		m_pointTimer += dt * 2.5;
		if (m_pointTimer >= 1) {
			addPoints(1);
			m_pointTimer = 0;
		}
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			for (int i = 0; i < 5; i++) {
				//create enemy
				std::string asteroid = "Asteroid1.png";
				int j = neko::random(4);
				if (j == 0) {
					asteroid = "Asteroid1.png";
				}
				else if (j == 1) {
					 asteroid = "Asteroid2.png";
				}
				else if (j == 2) {
					 asteroid = "Asteroid3.png";
				}
				else if (j == 3) {
					 asteroid = "Asteroid4.png";
				}
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(800.0f, 0, neko::Transform{ { 800.0f, neko::randomf(neko::g_renderer.getHeight()) }, neko::halfPi, 5});
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			//create components
			std::unique_ptr<neko::SpriteComponent> component = std::make_unique<neko::SpriteComponent>();
			component->m_texture = neko::g_resourceManager.get<neko::Texture>(asteroid, neko::g_renderer);
			enemy->addComponent(std::move(component));
			m_scene->add(std::move(enemy));
			}
		}
		if (m_powerupTimer <= 0) {
			// create powerup
			std::unique_ptr<Powerup> powerup = std::make_unique<Powerup>(0, neko::Transform{ { 800.0f, neko::randomf(neko::g_renderer.getHeight()) }, 0, 5});
			powerup->m_tag = "Powerup";
			powerup->m_game = this;
			// create components
			std::unique_ptr<neko::SpriteComponent> component = std::make_unique<neko::SpriteComponent>();
			component->m_texture = neko::g_resourceManager.get<neko::Texture>("Powerup.png", neko::g_renderer);
			powerup->addComponent(std::move(component));
			m_scene->add(std::move(powerup));
			m_powerupTimer = 32;
		}
		if (m_powerup == true && m_powerDuration > 0) {
			addPoints(1);
			m_powerDuration -= dt;
			if (m_powerDuration == 0) {
				m_powerDuration = 5;
			}
		}

		neko::g_particleSystem.update(neko::g_time.getDeltaTime());

		break;

	case H_AsteroidField::eState::PlayerDeadStart:
		m_stateTimer = 1;
		m_state = eState::PlayerDead;
		break;
	case H_AsteroidField::eState::PlayerDead:
		neko::g_audioSystem.playOneShot("damage");

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

		break;

	case H_AsteroidField::eState::GameOver:
		m_scene->removeAll();

		std::unique_ptr<Title> title = std::make_unique<Title>(neko::Transform{ { 400.0f, 250.0f }, neko::halfPi, 6});//, add sprite);
		title->m_tag = "Title";
		title->m_game = this;
		m_scene->add(std::move(title));
		if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE)) {
			m_scene->removeAll();
			m_state = eState::Title;
		}

		break;

	//default:
		//break;
	}

	m_scoreText->create(neko::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
	m_scene->update(dt);
}

void H_AsteroidField::draw(neko::Renderer& renderer) {
	if (m_state == eState::Title) {
		m_titleText->draw(renderer, 225, 250);
		m_subTitleText->draw(renderer, 225, 275);
	}
	if (m_state == eState::GameOver) {
		m_endText->draw(renderer, 50, 350);
	}

	m_scoreText->draw(renderer, 10, 10);
	m_highScoreText->draw(renderer, neko::g_renderer.getWidth() - 275, 10);
	m_scene->draw(renderer);

	for (auto& star : stars) {
		star.update(renderer.getWidth(), renderer.getWidth());
		star.draw(neko::g_renderer);
	}

	
	neko::g_particleSystem.draw(neko::g_renderer);
}
