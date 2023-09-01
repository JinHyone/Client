#include "GameObject.h"
#include "GameObject.h"
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "CameraCompoent.h"
#include "SceneMananger.h"
#include "DevScene.h"
#include "TileMapActor.h"
#include "TileMap.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Init()
{
	Super::Init();

	SetState(MOVE);
	SetState(IDLE);
}

void GameObject::Update()
{
	_dirtyFlag = false;

	Super::Update();

	switch (info.state())
	{
	case IDLE:
		TickIdle();
		break;
	case MOVE:
		TickMove();
		break;
	case SKILL:
		TickSkill();
		break;
	}
}

void GameObject::Render(HDC hdc)
{
	Super::Render(hdc);

}

void GameObject::SetState(ObjectState state)
{
	if (info.state() == state) return;

	info.set_state(state);
	UpdateAnimation();
	_dirtyFlag = true;
}

void GameObject::SetDir(Dir dir)
{
	info.set_dir(dir);
	UpdateAnimation();
	_dirtyFlag = true;
}

Dir GameObject::GetLookAtDir(Vec2Int cellPos)
{
	Vec2Int dir = cellPos - GetCellPos();
	if (dir.x > 0) return Dir::DIR_TYPE_RIGHT;
	else if (dir.x < 0) return Dir::DIR_TYPE_LEFT;
	else if (dir.y > 0) return  Dir::DIR_TYPE_DOWN;
	else return  Dir::DIR_TYPE_UP;
}

void GameObject::UpdateAnimation()
{
	
}

bool GameObject::HasReachedDest()
{
	Vec2 dir = (_destPos - _pos);
	return (dir.Length() < 5.f);
}

bool GameObject::CanGo(Vec2Int cellPos)
{
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneMananger)->GetCurrentScene());
	if (scene == nullptr)
		return false;

	return scene->CanGo(cellPos);
}

void GameObject::SetCellPos(Vec2Int cellPos, bool teleport)
{
	if (_layer == LAYER_OBJECT)
	{
		Tile* tile = GS(SceneMananger)->GetTileMapActor()->GetTileMap()->GetTileAt(cellPos);
		tile->creaturePtr = this;

		if (cellPos != GetCellPos())
		{
			tile = GS(SceneMananger)->GetTileMapActor()->GetTileMap()->GetTileAt(GetCellPos());
			tile->creaturePtr = nullptr;
		}
	}

	info.set_posx(cellPos.x);
	info.set_posy(cellPos.y);

	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneMananger)->GetCurrentScene());
	if (scene == nullptr) return;

	_destPos = scene->ConvertPos(cellPos);

	if (teleport)
		_pos = _destPos;

	_dirtyFlag = true;
}

Vec2Int GameObject::GetFrontCellPos()
{
	switch (info.dir())
	{
	case Dir::DIR_TYPE_DOWN:
		return GetCellPos() + Vec2Int{0, 1};
		break;
	case Dir::DIR_TYPE_LEFT:
		return GetCellPos() + Vec2Int{ -1, 0 };
		break;
	case Dir::DIR_TYPE_RIGHT:
		return GetCellPos() + Vec2Int{ 1, 0 };
		break;
	case Dir::DIR_TYPE_UP:
		return GetCellPos() + Vec2Int{ 0, -1 };
		break;
	}

	return GetCellPos();
}
