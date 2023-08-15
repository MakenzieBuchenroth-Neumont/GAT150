#pragma once
#include <string>
#include "Factory.h"
#include "Core/Json.h"

#define CLASS_DECLARATION(classname) \
	virtual const char* getClassName() { return #classname; } \
	bool read(const rapidjson::Value& value); \
	class Register { \
	public: \
		Register() { \
			Factory::Instance().reg<classname>(#classname); \
		} \
	};

#define CLASS_DEFINITION(classname) \
	classname::Register regis;

namespace neko {
	class Object {
	public:
		Object() = default;
		Object(const std::string& name) : name{ name } {}
		virtual ~Object() { onDestroy(); }
		
		CLASS_DECLARATION(Object)

		virtual bool initialize() { return true; }
		virtual void onDestroy() {}
		
	protected:
		std::string name;
	};
}