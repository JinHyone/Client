#pragma once
#include "GameObject.h"

class HitEffect : public GameObject
{
	using Super = GameObject;
public:
	HitEffect();
	virtual ~HitEffect() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void UpdateAnimation();
};

