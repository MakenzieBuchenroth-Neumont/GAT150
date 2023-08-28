#pragma once
#include <map>
#include <memory>
#include <string>
#include "Framework/Singleton.h"
#include "Resource.h"


#define GET_RESOURCE(type, filename, ...) neko::ResourceManager::Instance().get<type>(filename, __VA_ARGS__)

namespace neko {
	class ResourceManager : public Singleton<ResourceManager> {
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
		if (!resource->create(filename, args...))
		{
			WARNING_LOG("Could not create resource: " << filename);
			return res_t<T>();
		}

		m_resources[filename] = resource;
		return resource;
	}
}