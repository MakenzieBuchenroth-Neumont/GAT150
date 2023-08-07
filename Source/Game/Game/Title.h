#pragma once
#include "Framework/Actor.h"

class Title : public neko::Actor {
public:
	Title(const neko::Transform& transform) :
		neko::Actor{ transform }
	{}
	void update(float dt) override;

private:
};