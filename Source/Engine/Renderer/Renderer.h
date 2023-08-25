#pragma once
#include "Font.h"
#include "Highscore.h"
#include "Model.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Text.h"
#include "Texture.h"

#include <SDL2-2.28.0/include/SDL.h>
#include <string>

namespace neko {
	class Renderer {
	public:
		Renderer() = default;
		~Renderer() = default;

		bool initialize();
		void shutDown();

		void createWindow(const std::string& title, int width, int height);
		void beginFrame();
		void endFrame();

		void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		void drawLine(int x1, int y1, int x2, int y2);
		void drawPoint(int x, int y);
		void drawLine(float x1, float y1, float x2, float y2);
		void drawPoint(float x, float y);

		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }

		void drawTexture(class Texture* texture, float x, float y, float angle = 0.0f);
		void drawTexture(class Texture* texture, const Transform& transform);
		void drawTexture(class Texture* texture, const Rect& source, const Transform& transform);

		SDL_Renderer* m_renderer = nullptr;

		friend class Texture;
	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Window* m_window = nullptr;
	};


	extern Renderer g_renderer;
}