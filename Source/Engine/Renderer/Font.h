#pragma once
#include <string>
#include "Framework/Resource/Resource.h"

struct _TTF_Font;

namespace neko {
	class Font : public Resource {
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		virtual bool create(std::string filename, ...) override;
		bool load(const std::string& filename, int fontSize);

		_TTF_Font* m_ttfFont = nullptr;
	private:

	};
}