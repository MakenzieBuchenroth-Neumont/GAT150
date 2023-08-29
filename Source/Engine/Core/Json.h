#pragma once
#include "rapidjson/include/rapidjson/document.h"
#include <string>
#include <vector>
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Rect.h"

#define READ_DATA(value, data) neko::Json::read(value, #data, data)
#define READ_DATA_REQUIRED(value, data) neko::Json::read(value, #data, data, true)
#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]
#define READ_NAME_DATA(value, name, data) neko::Json::read(value, name, data)
#define READ_NAME_DATA_REQUIRED(value, name, data) neko::Json::read(value, name, data, true)

namespace neko {
	class Json {
	public:
		static bool load(const std::string& filename, rapidjson::Document& document);
		static bool read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, Color& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, Rect& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool required = false);
		static bool read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool required = false);
	};

	using json_t = rapidjson::Value;
}