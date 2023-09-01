#include "pch.h"
#include "TileMapActor.h"
#include "InputManager.h"
#include "SceneMananger.h"
#include "ResourceManager.h"
#include "TileMap.h"
#include "Sprite.h"

TileMapActor::TileMapActor()
{
}

TileMapActor::~TileMapActor()
{
}

void TileMapActor::Init()
{
	Super::Init();
}

void TileMapActor::Update()
{
	Super::Update();
	TilePicking();
}

void TileMapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_tileMap == nullptr) return;

	if (_showDebug == false) return;

	const Vec2Int mapSize = _tileMap->GetMapSize();
	const int32 tileSize = _tileMap->GetTileSize();

	vector<vector<Tile>>& tiles = _tileMap->GetTiles();

	Sprite* spriteO = GS(ResourceManager)->GetSprite(L"TileO");
	Sprite* spriteX = GS(ResourceManager)->GetSprite(L"TileX");

	Vec2 cameraPos = GS(SceneMananger)->GetCameraPos();

	int32 leftX, leftY, rightX, rightY,
		startX, startY, endX, endY;
	leftX = ((int32)cameraPos.x - GWinSizeX / 2);
	leftY = ((int32)cameraPos.y - GWinSizeY / 2);
	rightX = ((int32)cameraPos.x + GWinSizeX / 2);
	rightY = ((int32)cameraPos.y + GWinSizeY / 2);

	startX = (leftX - _pos.x) / TILE_SIZEX;
	startY = (leftY - _pos.y) / TILE_SIZEY;
	endX = (rightX - _pos.x) / TILE_SIZEX;
	endY = (rightY - _pos.y) / TILE_SIZEY;

	for (int32 y = startY; y <= endY; y++)
	{
		for (int32 x = startX; x <= endX; x++)
		{
			if (x < 0 || x >= mapSize.x) continue;
			if (y < 0 || y >= mapSize.y) continue;

			switch (tiles[y][x].value)
			{
				case 0:
					::TransparentBlt
					(
						hdc,
						_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
						_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
						TILE_SIZEX,
						TILE_SIZEY,
						spriteO->GetDC(),
						spriteO->GetPos().x,
						spriteO->GetPos().y,
						TILE_SIZEX,
						TILE_SIZEY,
						spriteO->GetTransparent()
					);
					break;
				case 1:
					::TransparentBlt
					(
						hdc,
						_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
						_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
						TILE_SIZEX,
						TILE_SIZEY,
						spriteX->GetDC(),
						spriteX->GetPos().x,
						spriteX->GetPos().y,
						TILE_SIZEX,
						TILE_SIZEY,
						spriteX->GetTransparent()
					);
					break;
			}
		}
	}
}

void TileMapActor::TilePicking()
{
	if (_canEdit == false) return;

	if (GS(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		Vec2 cameraPos = GS(SceneMananger)->GetCameraPos();
		int32 screenX = cameraPos.x - GWinSizeX / 2;
		int32 screenY = cameraPos.y - GWinSizeY / 2;

		POINT mousePos = GS(InputManager)->GetMousePos();
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;

		Tile* tile = _tileMap->GetTileAt({ x, y });
		if (tile) tile->value = 1;
	}
}
