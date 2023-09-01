#pragma once
#include "GameObject.h"

class Creature : public GameObject
{
	using Super = GameObject;
public:
	Creature();
	virtual ~Creature() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() override {};
	virtual void TickMove() override {};
	virtual void TickSkill() override {};
	virtual void UpdateAnimation() override {};

public:
	virtual void OnDamage(Creature* attacker);
	void SetStat(Stat stat) { _stat = stat; }
	Stat& GetStat() { return _stat; }

protected:
	Stat _stat;
};

