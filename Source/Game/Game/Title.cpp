#include "Title.h"
#include "Player.h"
#include "Weapon.h"
#include "H_AsteroidField.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"

namespace neko {
	CLASS_DEFINITION(Title);
	void Title::update(float dt) {
		Actor::update(dt);
	}

	void Title::read(const json_t& value) {
		Actor::read(value);
	}
}
