#include "pch.h"
#include "EditScene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include <fstream>

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
}

void EditScene::Init()
{
}

void EditScene::Update()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		if (_setOrigin)
		{
			_lastPos = mousePos;
			_setOrigin = false;
		}
		else
		{
			_lines.push_back({ _lastPos, mousePos });
			_lastPos = mousePos;
		}
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RighMouse))
		_setOrigin = true;


	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S))
	{
		wofstream file;
		file.open(L"Unit.txt");

		file << static_cast<int32>(_lines.size()) << endl;
		int32 minX, minY = minX = INT32_MAX, maxX, maxY = maxX = INT32_MIN;

		for (auto& line : _lines)
		{
			POINT from = line.first;
			POINT to = line.second;

			minX = min(min(minX, from.x), min(minX, to.x));
			minY = min(min(minY, from.y), min(minY, to.y));
			maxX = max(max(maxX, from.x), max(maxX, to.x));
			maxY = max(max(maxX, from.x), max(maxY, to.y));
		}

		for (auto& line : _lines)
		{
			POINT from = line.first;
			POINT to = line.second;

			int32 datumPointX = (minX + maxX) / 2;
			int32 datumPointY = (minY + maxX) / 2;

			from.x -= datumPointX; from.y -= datumPointY;
			to.x -= datumPointX; to.y -= datumPointY;

			wstring str = ::format(L"{0} {1} {2} {3}", from.x, from.y, to.x, to.y);
			file << str << endl;
		}

		file.close();
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
	{
		wifstream file;
		file.open(L"Unit.txt");

		int32 count;
		file >> count;

		_lines.clear();


		for (int32 i = 0; i < count; i++)
		{
			//POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
			//int32 datumX = mousePos.x, datumY = mousePos.y;

			POINT from, to;
			file >> from.x; file >> from.y;
			file >> to.x; file >> to.y;

			_lines.push_back({ from, to });
		}

		file.close();
	}
}

void EditScene::Render(HDC hdc)
{
	for (auto& line : _lines)
	{
		POINT pt1 = line.first;
		POINT pt2 = line.second;

		Pos pos1{ (float)pt1.x, (float)pt1.y };
		Pos pos2{ (float)pt2.x, (float)pt2.y };

		Utils::DrawLine(hdc, pos1, pos2);
	}
}
