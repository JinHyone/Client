#include "pch.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "TimeManager.h"
#include "SceneMananger.h"
#include "Texture.h"

FlipbookActor::FlipbookActor()
{
}

FlipbookActor::~FlipbookActor()
{
}

void FlipbookActor::Init()
{
	Super::Init();
}

void FlipbookActor::Update()
{
	Super::Update();

	if (_flipbook == nullptr) return;

	const FlipbookInfo info = _flipbook->GetFlipbokkInfo();
	if (info.loop == false && _idx == info.end) return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	int32 frameCount = (info.end - info.start) + 1;
	float delta = info.duration / frameCount;

	if (_sumTime >= delta)
	{
		_sumTime -= delta;
		_idx = (_idx + 1) % frameCount;
	}
}

void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);
	
	if (_flipbook == nullptr) return;

	const FlipbookInfo info = _flipbook->GetFlipbokkInfo();
	
	Vec2 cameraPos = GS(SceneMananger)->GetCameraPos();

	::TransparentBlt
	(
		hdc,
		(int32)_pos.x - info.size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
		(int32)_pos.y - info.size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		info.size.x,
		info.size.y,
		info.texture->GetDC(),
		(info.start + _idx) * info.size.x,
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent()
	);
}

void FlipbookActor::SetFlipbook(Flipbook* flipbook)
{
	if (flipbook && _flipbook == flipbook) return;
	_flipbook = flipbook;
	Reset();
}

void FlipbookActor::Reset()
{
	_sumTime = 0;
	_idx = _flipbook->GetFlipbokkInfo().start;
}

bool FlipbookActor::IsAnimaionEnded()
{
	if (_flipbook == nullptr) return true;

	const FlipbookInfo& info = _flipbook->GetFlipbokkInfo();

	if (info.loop == false && _idx == info.end) return true;

	return false;
}
