#pragma once
#include "rapidjson/include/rapidjson/document.h"
#include <string>
#include "Math/Vector2.h"

#define READ_DATA(value, data) neko::Json::read(value, #data, data);
#define READ_DATA_REQUIRED(value, data) neko::Json::read(value, #data, data, true);

namespace neko {
	class Json {
	public:
		static bool load(const std::string& filename, rapidjson::Document& document);
		static bool read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required = false);
	};
}