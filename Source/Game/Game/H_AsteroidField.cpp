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
	m_scene->load("scene.json");
	m_scene->initialize();

	return true;
}

void H_AsteroidField::shutdown() {
}

void H_AsteroidField::update(float dt) {
	int highScore = highscoreManager.readHighScore();
	m_scene->getActorByName("High")->getComponent<neko::TextRenderComponent>()->setText("HIGH SCORE " + std::to_string(highscoreManager.readHighScore()));
	//m_highScoreText->create(neko::g_renderer, "HIGH SCORE " + std::to_string(highscoreManager.readHighScore()), neko::Color(1, 1, 1, 1));

	switch (m_state) {
	case H_AsteroidField::eState::Title:
		if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
			neko::g_audioSystem.playOneShot("ui");
			//auto actor = m_scene->getActorByName("Background");
			//if (actor) actor->active = false;
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
		auto player = INSTANTIATE(Player, "Player");
		player->m_game = this;
		player->initialize();
		m_scene->add(std::move(player));
		/*
		std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, 0, neko::Transform{ {100.0f, 300.0f }, 0, 1});
		player->tag = "Player";
		player->m_game = this;
		//create components
		// sprite
		auto renderComponent = CREATE_CLASS(SpriteComponent)
		renderComponent->m_texture = GET_RESOURCE(neko::Texture, "falcon.png", neko::g_renderer);
		player->addComponent(std::move(renderComponent));
		// physics
		auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent)
		player->addComponent(std::move(physicsComponent));
		// collision
		auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
		collisionComponent->m_radius = 30.0f;
		player->addComponent(std::move(collisionComponent));

		player->initialize();
		m_scene->add(std::move(player));
		*/
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
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->m_game = this;
			enemy->initialize();
			enemy->getComponent<neko::SpriteComponent>()->m_texture = GET_RESOURCE(neko::Texture, asteroid, neko::g_renderer);
			enemy->transform = (neko::Transform{ { 800.0f, neko::randomf(neko::g_renderer.getHeight()) }, neko::halfPi, 1});
			m_scene->add(std::move(enemy));
			/*
			std::unique_ptr<neko::Enemy> enemy = std::make_unique<neko::Enemy>(800.0f, 0, neko::Transform{ { 800.0f, neko::randomf(neko::g_renderer.getHeight()) }, neko::halfPi, 1});
			enemy->tag = "Enemy";
			enemy->m_game = this;
			//create components
			// sprite
			auto spriteComponent = CREATE_CLASS(SpriteComponent)
			spriteComponent->m_texture = GET_RESOURCE(neko::Texture, asteroid, neko::g_renderer);
			enemy->addComponent(std::move(spriteComponent));
			// collision
			auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
			collisionComponent->m_radius = 30.0f;
			enemy->addComponent(std::move(collisionComponent));
			
			enemy->initialize();
			m_scene->add(std::move(enemy));*/
			}
		}
		if (m_powerupTimer <= 0) {
			// create powerup
			auto powerup = INSTANTIATE(Powerup, "Powerup");
			powerup->m_game = this;
			powerup->initialize();
			powerup->transform = (neko::Transform{ { 800.0f, neko::randomf(neko::g_renderer.getHeight()) }, 0, 1.5});
			m_scene->add(std::move(powerup));
			/*
			std::unique_ptr<Powerup> powerup = std::make_unique<Powerup>(0, neko::Transform{ { 800.0f, neko::randomf(neko::g_renderer.getHeight()) }, 0, 1.5});
			powerup->tag = "Powerup";
			powerup->m_game = this;
			// create components
			// sprite
			auto spriteComponent = CREATE_CLASS(SpriteComponent)
			spriteComponent->m_texture = GET_RESOURCE(neko::Texture, "Powerup.png", neko::g_renderer);
			powerup->addComponent(std::move(spriteComponent));
			// collision
			auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
			collisionComponent->m_radius = 30.0f;
			powerup->addComponent(std::move(collisionComponent));

			powerup->initialize();
			m_scene->add(std::move(powerup));
			*/
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
		auto title = INSTANTIATE(Title, "Title");
		title->m_game = this;
		title->initialize();
		m_scene->add(std::move(title));
		/*std::unique_ptr<Title> title = std::make_unique<Title>(neko::Transform{ { 400.0f, 250.0f }, neko::halfPi, 6});//, add sprite);
		title->tag = "Title";
		title->m_game = this;
		m_scene->add(std::move(title));*/
		if (neko::g_inputSystem.getKeyDown(SDL_SCANCODE_SPACE)) {
			m_scene->removeAll();
			m_state = eState::Title;
		}

		break;

	//default:
		//break;
	}

	m_scene->getActorByName("Score")->getComponent<neko::TextRenderComponent>()->setText(std::to_string(m_score));

	//m_scoreText->create(neko::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
	m_scene->update(dt);
}

void H_AsteroidField::draw(neko::Renderer& renderer) {
	m_scene->draw(renderer);
	if (m_state != eState::Title) {
		m_scene->getActorByName("Start")->active = false;
		m_scene->getActorByName("Subtitle")->active = false;
	}
	if (m_state != eState::GameOver) {
		m_scene->getActorByName("End")->active = false;
	}	
	if (m_state == eState::GameOver) {
		m_scene->getActorByName("End")->active = true;
	}
	for (auto& star : stars) {
		star.update(renderer.getWidth(), renderer.getWidth());
		star.draw(neko::g_renderer);
	}
	//m_scoreText->draw(renderer, 10, 10);
	//m_highScoreText->draw(renderer, neko::g_renderer.getWidth() - 275, 10);
	neko::g_particleSystem.draw(neko::g_renderer);
}