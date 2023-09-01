#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "CameraCompoent.h"
#include "SceneMananger.h"
#include "DevScene.h"
#include "HitEffect.h"
#include "Arrow.h"

Player::Player()
{
	_flipbookIdle[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleUp");
	_flipbookIdle[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleDown");
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleLeft");
	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleRight");

	_flipbookMove[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveUp");
	_flipbookMove[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveDown");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveLeft");
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveRight");

	_flipbookAttack[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackUp");
	_flipbookAttack[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackDown");
	_flipbookAttack[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackLeft");
	_flipbookAttack[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackRight");

	_flipbookBow[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BowUp");
	_flipbookBow[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BowDown");
	_flipbookBow[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BowLeft");
	_flipbookBow[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BowRight");

	_flipbookStaff[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_StaffUp");
	_flipbookStaff[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_StaffDown");
	_flipbookStaff[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_StaffLeft");
	_flipbookStaff[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_StaffRight");

	_stat.set_hp(100);
	_stat.set_maxhp(100);
	_stat.set_attack(30);
	_stat.set_defence(5);
}

Player::~Player()
{

}

void Player::Init()
{
	Super::Init();

	SetState(MOVE);
	SetState(IDLE);
}

void Player::Update()
{
	Super::Update();
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::TickIdle()
{
	SetPos(_destPos);
}

void Player::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	if (deltaTime > 0.05f) return;

	Vec2 dir = (_destPos - _pos);
	if (dir.Length() < 2.f)
	{
		SetState(IDLE);
		SetPos(_destPos);
	}
	else
	{
		switch (info.dir())
		{
		case DIR_UP:
			_pos.y -= 200 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 200 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 200 * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += 200 * deltaTime;
			break;
		}
	}
}

void Player::TickSkill()
{
	if (_flipbook == nullptr) return;

	if (IsAnimaionEnded())
	{
		// TODO : Damage
		DevScene* scene = dynamic_cast<DevScene*>(GS(SceneMananger)->GetCurrentScene());
		if (scene == nullptr) return;

		if (_weaponType == WeaponType::Sword)
		{
			Creature* creature = scene->GetCreatureAt(GetFrontCellPos());
			if (creature)
			{
				scene->SpawnObject<HitEffect>(GetFrontCellPos());
				creature->OnDamage(this);
			}
		}

		SetState(IDLE);
	}
}

void Player::UpdateAnimation()
{
	switch (info.state())
	{
	case IDLE:
			SetFlipbook(_flipbookIdle[info.dir()]);
		break;
	case MOVE:
		SetFlipbook(_flipbookMove[info.dir()]);
		break;
	case SKILL:
		switch (_weaponType)
		{
		case WeaponType::Sword:
			SetFlipbook(_flipbookAttack[info.dir()]);
			break;
		case WeaponType::Bow:
			SetFlipbook(_flipbookBow[info.dir()]);
			break;
		case WeaponType::Staff:
			SetFlipbook(_flipbookStaff[info.dir()]);
			break;
		}
		break;
	}
}