#pragma once
#include "Creature.h"

class Player;

class Monster : public Creature
{
	using Super = Creature;
public:
	Monster();
	virtual ~Monster() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickSkill() override;
	virtual void UpdateAnimation() override;

protected:
	Flipbook*	_flipbookMove[4] = {};
	Player*		_target = nullptr;
	float _waitSecond = 0.5f;
};

