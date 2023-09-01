#include "pch.h"
#include "Arrow.h"
#include "ResourceManager.h"
#include "SceneMananger.h"
#include "TimeManager.h"
#include "DevScene.h"
#include "Flipbook.h"
#include "Creature.h"
#include "HitEffect.h"

Arrow::Arrow()
{
	_flipbookMove[DIR_UP] = GS(ResourceManager)->GetFlipbook(L"FB_ArrowUp");
	_flipbookMove[DIR_DOWN] = GS(ResourceManager)->GetFlipbook(L"FB_ArrowDown");
	_flipbookMove[DIR_LEFT] = GS(ResourceManager)->GetFlipbook(L"FB_ArrowLeft");
	_flipbookMove[DIR_RIGHT] = GS(ResourceManager)->GetFlipbook(L"FB_ArrowRight");
}

Arrow::~Arrow()
{
}

void Arrow::Init()
{
	Super::Init();
}

void Arrow::Update()
{
	Super::Update();
	UpdateAnimation();
}

void Arrow::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Arrow::TickIdle()
{
	// TODO : Damage
	DevScene* scene = dynamic_cast<DevScene*>(GS(SceneMananger)->GetCurrentScene());
	if (scene == nullptr) return;

	Vec2Int nextPos = GetFrontCellPos();

	if (CanGo(nextPos))
	{
		SetCellPos(nextPos);
		SetState(MOVE);
	}
	else
	{
		Creature* creature = scene->GetCreatureAt(nextPos);
		if (creature)
		{
			scene->SpawnObject<HitEffect>(nextPos);
			// creature->OnDamage(this);
		}

		scene->RemoveActor(this);


	}
}

void Arrow::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (deltaTime > 0.005f) return;

	Vec2 dir = (_destPos - _pos);

	if (dir.Length() < 5.f)
	{
		SetState(ObjectState::OBJECT_STATE_TYPE_IDLE);
		_pos = _destPos;
	}
	else
	{
		switch (info.dir())
		{
		case DIR_UP:
			_pos.y -= 600 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 600 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 600 * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += 600 * deltaTime;
			break;
		}
	}
}

void Arrow::UpdateAnimation()
{
	SetFlipbook(_flipbookMove[info.dir()]);
}
