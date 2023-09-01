#include "pch.h"
#include "Utils.h"


void Utils::DrawTexts(HDC hdc, Pos pos, const wstring& str)
{
	::TextOut(hdc, pos.x, pos.y, str.c_str(), static_cast<int32>(str.size()));
}

void Utils::DrawRect(HDC hdc, Pos pos, int32 w, int32 h)
{
	::Rectangle(hdc, pos.x - w / 2, pos.y - h / 2, pos.x + w / 2, pos.y + h / 2);
}

void Utils::DrawCircle(HDC hdc, Pos pos, int32 radius)
{
	::Ellipse(hdc, pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);
}

void Utils::DrawLine(HDC hdc, Pos from, Pos to)
{
	MoveToEx(hdc, from.x, from.y, nullptr);
	::LineTo(hdc, to.x, to.y);
}
