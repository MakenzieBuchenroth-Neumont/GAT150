#pragma once
#include <memory>

namespace neko {

	class Scene;
	class Renderer;

	class Game {
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool initialize() = 0;
		virtual void shutdown() = 0;

		virtual void update(float dt) = 0;
		virtual void draw(Renderer& renderer) = 0;

		int getScore() const { return m_score;  }
		void addPoints(int points) { m_score += points; }

		int getLives() const { return m_lives; }
		void setLives(int lives) { m_lives = lives; }

		std::unique_ptr<Scene> m_scene;
	protected:

		int m_score = 0;
		int m_lives = 0;
	};
}