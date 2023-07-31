#pragma once
#include <string>

struct _TTF_Font;

namespace neko {
	class Font {
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		void load(const std::string& filename, int fontSize);

		_TTF_Font* m_ttfFont = nullptr;
	private:
	};
}