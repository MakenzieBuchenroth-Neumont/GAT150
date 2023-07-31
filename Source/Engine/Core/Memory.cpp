#include "Memory.h"
#include <iostream>

namespace neko {
	bool MemoryTracker::initialize() {
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		return true;
	}

	void MemoryTracker::displayInfo() {
		_CrtMemDumpAllObjectsSince(NULL);
	}
}