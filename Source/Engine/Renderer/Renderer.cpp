#include "Renderer.h"
#include "SDL2-2.28.0/include/SDL_ttf.h"

namespace neko {
	Renderer g_renderer;

	bool Renderer::initialize() {
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();

		return true;
	}

	void Renderer::shutDown() {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		TTF_Quit();
	}

	void Renderer::createWindow(const std::string& title, int width, int height) {
		m_width = width;
		m_height = height;

		m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}

	void Renderer::beginFrame() {
		SDL_RenderClear(m_renderer);
	}

	void Renderer::endFrame() {
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	}

	void Renderer::drawLine(int x1, int y1, int x2, int y2) {
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::drawPoint(int x, int y) {
		SDL_RenderDrawPoint(m_renderer, x, y);
	}

	void Renderer::drawLine(float x1, float y1, float x2, float y2) {
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::drawPoint(float x, float y) {
		SDL_RenderDrawPointF(m_renderer, x, y);
	}
}