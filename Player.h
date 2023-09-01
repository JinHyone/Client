#pragma once
#include "Creature.h"

class Flipbook;

class Player : public Creature
{
	using Super = Creature;
public:
	Player();
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickSkill() override;
	virtual void UpdateAnimation() override;

	void SetWeaponType(WeaponType weaponType) { _weaponType = weaponType; }
	WeaponType GetWeaponType() { return _weaponType; }

private:
	Flipbook* _flipbookIdle[4] = {};
	Flipbook* _flipbookMove[4] = {};
	Flipbook* _flipbookAttack[4] = {};
	Flipbook* _flipbookBow[4] = {};
	Flipbook* _flipbookStaff[4] = {};

	WeaponType _weaponType = WeaponType::Sword;
};

