#pragma once


class UI
{
public:
	UI();
	virtual ~UI();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() { return _pos; }

	void SetSize(Vec2Int size) { _size = size; }
	Vec2Int GetSize() { return _size; }

	RECT GetRect();
	bool IsMouseInRect();

protected:
	Vec2 _pos = { 200, 200 };
	Vec2Int _size = { 150, 150 };
};

