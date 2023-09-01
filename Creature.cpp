#include "pch.h"
#include "Creature.h"
#include "SceneMananger.h"
#include "Scene.h"
#include "TileMapActor.h"
#include "TileMap.h"

Creature::Creature()
{
}

Creature::~Creature()
{

}

void Creature::Init()
{
	Super::Init();
}

void Creature::Update()
{
	Super::Update();
}

void Creature::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Creature::OnDamage(Creature* attacker)
{
	if (attacker == nullptr) return;

	Stat& attackerStat = attacker->GetStat();
	Stat& myStat = GetStat();

	int32 damage = attackerStat.attack() - myStat.defence();

	if (damage < 0) return;

	myStat.set_hp(max(0, myStat.hp() - damage));

	if (myStat.hp() == 0)
	{
		Scene* scene = GS(SceneMananger)->GetCurrentScene();
		if (scene)
		{
			scene->RemoveActor(this);
		}
	}
}
