#pragma once
#include <string>
#include <memory>

namespace neko {
	class Resource {
	public:
		virtual ~Resource() = default;

		virtual bool create(std::string filename, ...) = 0;

	};

	template<typename T>
	using res_t = std::shared_ptr<T>;
}