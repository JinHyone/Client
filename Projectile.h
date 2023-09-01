#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
	using Super = GameObject;
public:
	Projectile();
	virtual ~Projectile() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() {};
	virtual void TickMove() {};
	virtual void TickSkill() {};
	virtual void UpdateAnimation();
};

