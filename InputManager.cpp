#include "pch.h"
#include "InputManager.h"

InputManager* InputManager::s_instance = nullptr;

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None);
}

void InputManager::Update()
{
	BYTE ascilKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(ascilKeys) == false) return;
	
	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		if (ascilKeys[key] & 0x80)
		{
			KeyState& state = _states[key];

			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Press;
			else state = KeyState::Down;
		}
		else
		{
			KeyState& state = _states[key];

			if (state == KeyState::Press || state == KeyState::Down)
				state = KeyState::Up;
			else state = KeyState::None;
		}
	}

	::GetCursorPos(&_mousePos);
	::ScreenToClient(_hwnd, &_mousePos);
}
