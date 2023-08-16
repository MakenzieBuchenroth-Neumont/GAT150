#include "Object.h"

namespace neko {
	void Object::read(const rapidjson::Value& value) {
		READ_DATA(value, name);
	}
}