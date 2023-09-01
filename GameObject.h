#pragma once
#include "FlipbookActor.h"

class GameObject : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	GameObject();
	virtual ~GameObject() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() {};
	virtual void TickMove() {};
	virtual void TickSkill() {};
	virtual void UpdateAnimation();

public:
	void SetState(ObjectState state);
	void SetDir(Dir dir);
	Dir  GetLookAtDir(Vec2Int cellPos);

public:
	bool HasReachedDest();
	bool CanGo(Vec2Int cellPos);

	void SetCellPos(Vec2Int cellPos, bool teleport = false);

	Vec2Int GetCellPos() { return Vec2Int(info.posx(), info.posy()); }
	Vec2Int GetFrontCellPos();

	uint64 GetObjectID() { return info.objectid(); }
	void SetObjectID(uint64 id) { info.set_objectid(id); }

protected:
	bool _dirtyFlag = false;

public:
	Protocol::ObjectInfo info;
};

