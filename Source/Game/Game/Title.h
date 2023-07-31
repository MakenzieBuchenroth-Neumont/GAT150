#pragma once
#include "Framework/Actor.h"

class Title : public neko::Actor {
public:
	Title(const neko::Transform& transform, std::shared_ptr<neko::Model> model) :
		neko::Actor{ transform, model }
	{}
	void update(float dt) override;

private:
};