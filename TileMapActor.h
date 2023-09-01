#pragma once
#include "Actor.h"

class TileMap;

class TileMapActor : public Actor
{
	using Super = Actor;
public:
	TileMapActor();
	virtual ~TileMapActor();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void TilePicking();

	void SetTileMap(TileMap* tileMap) { _tileMap = tileMap; }
	TileMap* GetTileMap() { return _tileMap; }

	void SetSHowDebug(bool showDebug) { _showDebug = showDebug; }
	void SetCanEdit(bool canEdit) { _canEdit = canEdit; }
	bool GetCanEdit() { return _canEdit; }

protected:
	TileMap*	_tileMap = nullptr;
	bool		_showDebug = false;
	bool		_canEdit = false;
};