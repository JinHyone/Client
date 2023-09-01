#include "pch.h"
#include "UI.h"
#include "InputManager.h"
#include "SceneMananger.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Init()
{
}

void UI::Update()
{
}

void UI::Render(HDC hdc)
{
}

RECT UI::GetRect()
{
	Vec2 cameraPos = GS(SceneMananger)->GetCameraPos();

	RECT rect =
	{
		_pos.x - _size.x / 2 - (cameraPos.x - GWinSizeX / 2),
		_pos.y - _size.y / 2 - (cameraPos.y - GWinSizeY / 2),
		_pos.x + _size.x / 2 - (cameraPos.x - GWinSizeX / 2),
		_pos.y + _size.y / 2 - (cameraPos.y - GWinSizeY / 2)
	};

	return rect;
}

bool UI::IsMouseInRect()
{
	RECT rect = GetRect();
	POINT mousePos = GS(InputManager)->GetMousePos();

	return ::PtInRect(&rect, mousePos);
}
