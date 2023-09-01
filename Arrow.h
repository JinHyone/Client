#pragma once
#include "Projectile.h"

class Arrow : public Projectile
{
	using Super = Projectile;
public:
	Arrow();
	virtual ~Arrow() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void UpdateAnimation() override;

private:
	Flipbook* _flipbookMove[4] = {};
};

