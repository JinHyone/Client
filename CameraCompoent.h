#pragma once
#include "Compoent.h"

class CameraCompoent : public Compoent
{
public:
	CameraCompoent();
	virtual ~CameraCompoent();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

