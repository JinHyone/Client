#pragma once
#include "Actor.h"

class Flipbook;

class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor();
	virtual ~FlipbookActor();

	virtual void	Init() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;

	void			SetFlipbook(Flipbook* flipbook);
	void			Reset();

	bool			IsAnimaionEnded();

protected:
	Flipbook* _flipbook = nullptr;
	float _sumTime = 0.f;
	int32 _idx = 0;
};

