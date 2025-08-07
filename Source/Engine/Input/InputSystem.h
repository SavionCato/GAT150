#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include <array>

namespace Rex {
	class InputSystem {
	public:
		enum class MouseButton : uint8_t {
			Left,
			Middle,
			Right
		};

	public:
		InputSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		// KEYBOARD INPUT
		bool GetKeyDown(uint8_t key) const { return s_keyboardState[key]; }
		bool GetPreviousKeyDown(uint8_t key) const { return s_prevKeyboardState[key]; }
		bool GetKeyPressed(uint8_t key) const { return !s_prevKeyboardState[key] && s_keyboardState[key]; }
		bool GetKeyReleased(uint8_t key) const { return s_prevKeyboardState[key] && !s_keyboardState[key]; }

		// MOUSE INPUT
		bool GetMouseButtonDown(MouseButton button) { return s_mouseButtonState[(uint8_t)button]; }
		bool GetPreviousMouseButtonDown(MouseButton button) { return s_prevMouseButtonState[(uint8_t)button]; }
		bool GetMouseButtonPressed(MouseButton button) { return !s_prevMouseButtonState[(uint8_t)button] && s_mouseButtonState[(uint8_t)button]; }
		bool GetMouseButtonReleased(MouseButton button) { return s_prevMouseButtonState[(uint8_t)button] && !s_mouseButtonState[(uint8_t)button]; }

		const vec2& GetMousePosition() const { return s_mousePosition; }
		const vec2& GetPreviousMousePosition() const { return s_prevMousePosition; }

	private:
		std::vector<bool> s_keyboardState;
		std::vector<bool> s_prevKeyboardState;

		Rex::vec2 s_mousePosition{ 0, 0 };
		Rex::vec2 s_prevMousePosition{ 0, 0 };

		std::array<bool, 3> s_mouseButtonState{ false, false, false };
		std::array<bool, 3> s_prevMouseButtonState{ false, false, false };
	};
}