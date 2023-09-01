#pragma once
#include <string>


class Utils
{
public:
	static void DrawTexts(HDC hdc, Pos pos, const std::wstring& str);
	static void DrawRect(HDC hdc, Pos pos, int32 w, int32 h);
	static void DrawCircle(HDC hdc, Pos pos, int32 radius);
	static void DrawLine(HDC hdc, Pos from, Pos to);
};

