#pragma once
#include <map>
#include <memory>
#include <string>

#include "Resource.h"

namespace neko {
	class ResourceManager {
	public:
		template<typename T, typename ... TArgs>
		res_t<T> get(const std::string& filename, TArgs ... args);

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};

	template<typename T, typename ... TArgs>
	inline res_t<T> ResourceManager::get(const std::string& filename, TArgs ... args) {
		if (m_resources.find(filename) != m_resources.end()) {
			return std::dynamic_pointer_cast<T>(m_resources[filename]);
		}

		res_t<T> resource = std::make_shared<T>();
		resource->create(filename, args...);
		m_resources[filename] = resource;

		return resource;
	}

	extern ResourceManager g_resourceManager;

}