#include "pch.h"
#include "MyPlayer.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CameraCompoent.h"
#include "SceneMananger.h"
#include "DevScene.h"
#include "ClientPacketHandler.h"
#include "NetWorkManager.h"
#include "ServerSession.h"

MyPlayer::MyPlayer()
{
	CameraCompoent* camera = new CameraCompoent();
	AddCompoent(camera);
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::Init()
{
	Super::Init();
}

void MyPlayer::Update()
{
	Super::Update();
	SyncToServer();
}

void MyPlayer::Render(HDC hdc)
{
	Super::Render(hdc);
}

void MyPlayer::TickInput()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_keyPressed = true;
	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		SetDir(DIR_UP);

	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetDir(DIR_DOWN);

	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
	}
	else
	{
		_keyPressed = false;
	}

	if (GS(InputManager)->GetButtonDown(KeyType::KEY_1))
	{
		SetWeaponType(WeaponType::Sword);
	}
	else if (GS(InputManager)->GetButtonDown(KeyType::KEY_2))
	{
		SetWeaponType(WeaponType::Bow);
	}
	else if (GS(InputManager)->GetButtonDown(KeyType::KEY_3))
	{
		SetWeaponType(WeaponType::Staff);
	}

	if (GS(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		SetState(SKILL);
	}
}

void MyPlayer::TryMove()
{
	if (_keyPressed == false) return;

	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	if (info.dir() == DIR_UP)
	{
		Vec2Int nextPos = GetCellPos() + deltaXY[info.dir()];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(MOVE);
		}
	}
	else if (info.dir() == DIR_DOWN)
	{
		Vec2Int nextPos = GetCellPos() + deltaXY[info.dir()];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(MOVE);
		}
	}
	else if (info.dir() == DIR_LEFT)
	{
		Vec2Int nextPos = GetCellPos() + deltaXY[info.dir()];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(MOVE);
		}
	}
	else if (info.dir() == DIR_RIGHT)
	{
		Vec2Int nextPos = GetCellPos() + deltaXY[info.dir()];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(MOVE);
		}
	}
}

void MyPlayer::TickIdle()
{
	TickInput();
	TryMove();
}

void MyPlayer::TickMove()
{
	Super::TickMove();
}

void MyPlayer::TickSkill()
{
	Super::TickSkill();
}

void MyPlayer::SyncToServer()
{
	if (_dirtyFlag == false) return;

	SendBufferRef sendBuffer = ClientPacketHandler::Make_C_Move();
	GS(NetWorkManager)->SendPacket(sendBuffer);
}
