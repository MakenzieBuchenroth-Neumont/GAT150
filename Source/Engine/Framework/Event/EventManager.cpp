#include "EventManager.h"
#include "Core/Logger.h"

namespace neko {
	void EventManager::update(float dt) {
	}

	void EventManager::subscribe(Event::id_t id, IEventListener* listener, eventFunction function) {
		eventDispatcher dispatcher;

		dispatcher.listener = listener;
		dispatcher.function = function;

		INFO_LOG("Event subscribed: " << id);

		m_dispatchers[id].push_back(dispatcher);
	}

	void EventManager::unsubscribe(Event::id_t id, IEventListener* listener) {
	}

	void EventManager::dispatchEvent(Event::id_t id, Event::data_t data)  {
		Event event{ id, data };

		if (m_dispatchers.find(id) != m_dispatchers.end()) {
			auto dispatchers = m_dispatchers[id];
			for (auto& dispatcher : dispatchers) {
				dispatcher.function(event);
			}
		}
	}
}