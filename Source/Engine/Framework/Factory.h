#pragma once
#include "Singleton.h"
#include <string>
#include <memory>
#include <map>

namespace neko {
	class CreatorBase {
	public:
		virtual ~CreatorBase() = default;

		virtual std::unique_ptr<class Object> create() = 0;
	};

	template <typename T>
	class Creator : public CreatorBase {
	public:
		std::unique_ptr<class Object> create() override {
			return std::make_unique<T>();
		}
	};

	class Factory : public Singleton<Factory> {
	public:
		template <typename T>
		void reg(const std::string& key);

		template <typename T>
		std::unique_ptr<T> create(const std::string& key);

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;

	};

	template<typename T>
	inline void Factory::reg(const std::string& key) {
		m_registry[key] = std::make_unique<Creator<T>>();
	}

	template<typename T>
	inline std::unique_ptr<T> Factory::create(const std::string& key) {
		auto iter = m_registry.find(key);
		if (iter != m_registry.end()) {
			return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->create().release()));
		}
		return std::unique_ptr<T>();
	}
}