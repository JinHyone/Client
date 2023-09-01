#pragma once
#include "Player.h"

class MyPlayer : public Player
{
	using Super = Player;
public:
	MyPlayer();
	virtual ~MyPlayer() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	void TickInput();
	void TryMove();

	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickSkill() override;

	void SyncToServer();

private:
	bool _keyPressed = false;
};

