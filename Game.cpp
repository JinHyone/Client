#include "pch.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneMananger.h"
#include "ResourceManager.h"
#include "NetWorkManager.h"
#include "Game.h"
#include "SoundManager.h"

Game::Game()
{
	
}

Game::~Game()
{
	_CrtDumpMemoryLeaks();
	GET_SINGLE(SceneMananger)->Clear();
	GET_SINGLE(ResourceManager)->Clear();
}

void Game::Init(HWND hwnd)
{
	_hWnd = hwnd;
	_hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	_hdcBack = ::CreateCompatibleDC(_hdc);
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
	HBITMAP prev = (HBITMAP) SelectObject(_hdcBack, _bmpBack);
	::DeleteObject(prev);

	GS(SoundManager)->Init(hwnd);
	GS(ResourceManager)->Init(hwnd, fs::path(L"E:\\VS repo\\WinGameCoding\\Resources"));
	GS(TimeManager)->Init();
	GS(InputManager)->Init(hwnd);
	GS(SceneMananger)->Init();

	GS(SceneMananger)->ChangeScene(SceneType::DevScene);

	GS(NetWorkManager)->Init();
}

void Game::Update()
{
	GS(TimeManager)->Update();
	GS(InputManager)->Update();
	GS(SceneMananger)->Update();
	GS(NetWorkManager)->Update();
}

void Game::Render()
{;
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	GET_SINGLE(SceneMananger)->Render(_hdcBack);

	{
		wstring bf = format(L"{0}fps  DT: {1}ms", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdcBack, 650, 10, bf.c_str(), static_cast<int>(bf.size()));
	}

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring mousePosStr = format(L"(x: {0}, y: {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 50, 10, mousePosStr.c_str(), static_cast<int>(mousePosStr.size()));
	}
	// 더블 버터링 
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
