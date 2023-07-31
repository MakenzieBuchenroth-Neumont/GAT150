#pragma once
#include <SDL2-2.28.0/include/SDL.h>
#include <vector>
#include <array>
#include "Core/Core.h"

namespace neko {
	class InputSystem {
	public:
		InputSystem() = default;
		~InputSystem() = default;

		bool initialize();
		void shutdown();

		void update();

		bool getKeyDown(uint32_t key) const { return m_keyboardState[key]; }
		bool getPreviousKeyDown(uint32_t key) const { return m_prevKeyboardState[key]; }

		const Vector2& getMousePosition() const { return m_mousePosition; }
		bool getMouseButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool getMousePreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }
	private:
		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;
		Vector2 m_mousePosition;
		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;
	};

	extern InputSystem g_inputSystem;
}