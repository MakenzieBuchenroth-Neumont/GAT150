#include "Font.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>
#include <Core/Logger.h>


neko::Font::Font(const std::string& filename, int fontSize) {
	load(filename, fontSize);
}

neko::Font::~Font() {
	if (m_ttfFont != nullptr) {
		TTF_CloseFont(m_ttfFont);
	}

}

bool neko::Font::create(std::string filename, ...) {
	va_list args;

	va_start(args, filename);
	int fontSize = va_arg(args, int);
	va_end(args);

	return load(filename, fontSize);
}

bool neko::Font::load(const std::string& filename, int fontSize) {
	m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
	if (m_ttfFont == nullptr) {
		WARNING_LOG("Failed to open font: " << filename);
		return false;
	}

	return true;
}

