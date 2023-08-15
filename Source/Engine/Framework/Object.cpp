#include "Object.h"

namespace neko {
	bool Object::read(const rapidjson::Value& value) {
		READ_DATA(value, name)

		return true;
	}
}