#include "InputSystem.h"
#include <SDL3/SDL.h>

namespace Rex {
    bool InputSystem::Initialize() {
        int numKeys;
        const bool* keyboardState = SDL_GetKeyboardState(&numKeys);
        
        s_keyboardState.resize(numKeys);
        std::copy(keyboardState, keyboardState + numKeys, s_keyboardState.begin());
        s_prevKeyboardState = s_keyboardState;
    
        SDL_GetMouseState(&s_mousePosition.x, &s_mousePosition.y);
        s_prevMousePosition = s_mousePosition;

        return true;
    }

    void InputSystem::Shutdown() {
        //
    }

    void InputSystem::Update() {
        // keyboard input
        s_prevKeyboardState = s_keyboardState;
        const bool* keyboardState = SDL_GetKeyboardState(nullptr);
        std::copy(keyboardState, keyboardState + s_keyboardState.size(), s_keyboardState.begin());

        // mouse input
        s_prevMousePosition = s_mousePosition;

        s_prevMouseButtonState = s_mouseButtonState;
        uint32_t mouseButtonState = SDL_GetMouseState(&s_mousePosition.x, &s_mousePosition.y);

        s_mouseButtonState[(uint8_t)MouseButton::Left] = mouseButtonState & SDL_BUTTON_LMASK;
        s_mouseButtonState[(uint8_t)MouseButton::Middle] = mouseButtonState & SDL_BUTTON_MMASK;
        s_mouseButtonState[(uint8_t)MouseButton::Right] = mouseButtonState & SDL_BUTTON_RMASK;
    }

}