#include "Font.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>

neko::Font::Font(const std::string& filename, int fontSize) {
	load(filename, fontSize);
}

neko::Font::~Font() {
	if (m_ttfFont != nullptr) {
		TTF_CloseFont(m_ttfFont);
	}

}

void neko::Font::load(const std::string& filename, int fontSize) {
	m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
}
