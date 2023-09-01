#pragma once

class Game
{
public:
	Game();
	~Game();

	void	Init(HWND hwnd);
	void	Update();
	void	Render();

private:
	HWND	_hWnd = {};
	HDC		_hdc = {};

private:
	RECT _rect = {};
	HDC  _hdcBack = {};
	HBITMAP _bmpBack = {};
};