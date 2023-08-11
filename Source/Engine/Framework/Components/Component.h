#pragma once
#include "Framework/Object.h"	

namespace neko {
	class Component : public Object {
	public:
		virtual void update(float dt) = 0;

		friend class Actor;

	public:
		class Actor* m_owner = nullptr;
	};
}
