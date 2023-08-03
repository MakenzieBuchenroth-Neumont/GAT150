#pragma once
#include <string>

namespace neko {
	class Resource {
		virtual ~Resource() = default;

		virtual bool create(std::string& filename, ...) = 0;

	};
}