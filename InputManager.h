#pragma once

enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RighMouse = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,
	SpaceBar = VK_SPACE,

	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Q = 'Q',
	E = 'E',
};

enum class KeyState
{
	None,
	Press,
	Down,
	Up,

	End,
};

enum
{
	KEY_TYPE_COUNT = static_cast<uint32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End)
};

class InputManager
{
	GNERATE_SINGLE(InputManager);

public:
	void Init(HWND hwnd);
	void Update();

	bool GetButton(KeyType key) { return GetState(key) == KeyState::Press; }
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	POINT GetMousePos() { return _mousePos; }
	
private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }

private:
	HWND _hwnd = 0;
	vector<KeyState> _states;
	POINT _mousePos{};
};

