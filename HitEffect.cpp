#include "pch.h"
#include "HitEffect.h"
#include "ResourceManager.h"
#include "SceneMananger.h"
#include "Scene.h"

HitEffect::HitEffect()
{
	SetLayer(LAYER_EFFECT);
}

HitEffect::~HitEffect()
{
}

void HitEffect::Init()
{
	Super::Init();
	UpdateAnimation();
}

void HitEffect::Update()
{
	Super::Update();

	if (IsAnimaionEnded())
	{
		Scene* scene = GS(SceneMananger)->GetCurrentScene();
		scene->RemoveActor(this);
		return;
	}
}

void HitEffect::Render(HDC hdc)
{
	Super::Render(hdc);
}

void HitEffect::UpdateAnimation()
{
	SetFlipbook(GS(ResourceManager)->GetFlipbook(L"FB_Hit"));
}
