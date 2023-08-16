#pragma once
#include "Singleton.h"
#include "Core/Logger.h"
#include <string>
#include <memory>
#include <map>

#define CREATE_CLASS(classname) neko::Factory::Instance().create<neko::classname>(#classname);
#define CREATE_CLASS_BASE(classbase, classname) neko::Factory::Instance().create<neko::classbase>(#classname);

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

		friend class Singleton;

	protected:
		Factory() = default;

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;

	};

	template<typename T>
	inline void Factory::reg(const std::string& key) {
		INFO_LOG("Class registered: " << key);
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