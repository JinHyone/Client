#include "pch.h"
#include "Monster.h"
#include "ResourceManager.h"
#include "DevScene.h"
#include "SceneMananger.h"
#include "Player.h"
#include "TimeManager.h"
#include "HitEffect.h"

Monster::Monster()
{
	_flipbookMove[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeUp");
	_flipbookMove[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeDown");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeLeft");
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SnakeRight");
}

Monster::~Monster()
{
}

void Monster::Init()
{
	Super::Init();

	SetState(MOVE);
	SetState(IDLE);

	_stat.set_hp(50);
	_stat.set_maxhp(50);
	_stat.set_attack(10);
	_stat.set_defence(0);
}

void Monster::Update()
{
	Super::Update();
}

void Monster::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Monster::TickIdle()
{
	
}

void Monster::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (deltaTime > 0.005f) return;

	Vec2 dir = (_destPos - _pos);

	if (dir.Length() < 5.f)
	{
		SetState(IDLE);
		_pos = _destPos;
	}
	else
	{
		bool horizontal = abs(dir.x) > abs(dir.y);
		if (horizontal) SetDir(dir.x < 0 ? DIR_LEFT : DIR_RIGHT);
		else SetDir(dir.y < 0 ? DIR_UP : DIR_DOWN);

		switch (info.dir())
		{
		case DIR_UP:
			_pos.y -= 50 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 50 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 50 * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += 50 * deltaTime;
			break;
		}
	}
}

void Monster::TickSkill()
{
	if (_flipbook == nullptr) return;

	if (_waitSecond > 0)
	{
		float deltaTime = GS(TimeManager)->GetDeltaTime();
		if (deltaTime > 0.05f) return;
		_waitSecond = max(0, _waitSecond - deltaTime);
		return;
	}

	_waitSecond = 0.5f;

	DevScene* scene = dynamic_cast<DevScene*>(GS(SceneMananger)->GetCurrentScene());
	if (scene == nullptr) return;

	Creature* creature = scene->GetCreatureAt(GetFrontCellPos());
	if (creature)
	{
		scene->SpawnObject<HitEffect>(GetFrontCellPos());
		creature->OnDamage(this);
	}
}

void Monster::UpdateAnimation()
{
	SetFlipbook(_flipbookMove[info.dir()]);
}
