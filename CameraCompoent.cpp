#include "pch.h"
#include "CameraCompoent.h"
#include "SceneMananger.h"

CameraCompoent::CameraCompoent()
{
}

CameraCompoent::~CameraCompoent()
{
}

void CameraCompoent::Init()
{
}

void CameraCompoent::Update()
{
	if (_owner == nullptr) return;

	Vec2 pos = _owner->GetPos();

	pos.x = ::clamp(pos.x, 400.f, 3024.f - 400.f);
	pos.y = ::clamp(pos.y, 300.f, 2064.f - 300.f);
	GS(SceneMananger)->SetCameraPos(pos);
}

void CameraCompoent::Render(HDC hdc)
{
}
