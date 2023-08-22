#pragma once
#include "Event.h"
#include "Framework/Singleton.h"
#include <map>
#include <list>
#include <functional>

namespace neko {
#define EVENT_SUBSCRIBE(id, function)	neko::EventManager::Instance().subscribe(id, this, std::bind(&function, this, std::placeholders::_1))
#define EVENT_UNSUBSCRIBE(id)			neko::EventManager::Instance().unsubscribe(id, this)

	class IEventListener {
		//
	};

	class EventManager : public Singleton<EventManager> {
	public:
		using eventFunction = std::function<void(const Event&)>;

		struct eventDispatcher {
			IEventListener* listener = nullptr; // object that can listen for events
			eventFunction function; // function that is called on event

		};
	public:
		void update(float dt);

		void subscribe(Event::id_t id, IEventListener* listener, eventFunction function);
		void unsubscribe(Event::id_t id, IEventListener* listener);

		void dispatchEvent(Event::id_t id, Event::data_t data);

		friend class Singleton;

	private:
		EventManager() = default;

	private:
		std::map<Event::id_t, std::list<eventDispatcher>> m_dispatchers;

	};
}