#pragma once
#include "Actor.h"

class Sprite;

class SpriteActor : public Actor
{
	using Super = Actor;
public:
	SpriteActor();
	virtual ~SpriteActor() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetSprite(Sprite* sprite) { _sprite = sprite; }

protected:
	Sprite* _sprite = nullptr;
};

