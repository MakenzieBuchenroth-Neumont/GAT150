#pragma once
#include <string>

namespace neko {
	class Object {
	public:
		Object() = default;
		Object(const std::string& name) : m_name{ name } {}
		virtual ~Object() { onDestroy(); }
		
		virtual bool initialize() { return true; }
		virtual void onDestroy() {}
		
	protected:
		std::string m_name;
	};
}