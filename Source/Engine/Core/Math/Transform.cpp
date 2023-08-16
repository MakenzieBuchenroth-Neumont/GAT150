#include "Transform.h"

namespace neko {
	void neko::Transform::read(const json_t& value) {
		READ_DATA(value, position);
		READ_DATA(value, rotation);
		READ_DATA(value, scale);

	}
}