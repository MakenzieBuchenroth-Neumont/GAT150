#pragma once

namespace neko {
	class Component {
	public:
		virtual void update(float dt) = 0;

		friend class Actor;

	protected:
		class Actor* m_owner = nullptr;
	};
}
