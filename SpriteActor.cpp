#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SceneMananger.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::Init()
{
	Super::Init();
}

void SpriteActor::Update()
{
	Super::Update();
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2Int size = _sprite->GetSize();

	if (_sprite == nullptr) return;

	Vec2 cameraPos = GS(SceneMananger)->GetCameraPos();

	::BitBlt
	(
		hdc,
		(int32)_pos.x - size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
		(int32)_pos.y - size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		size.x,
		size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		SRCCOPY
	);

	//::TransparentBlt
	//(
	//	hdc,
	//	(int32)_pos.x - size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
	//	(int32)_pos.y - size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
	//	size.x,
	//	size.y,
	//	_sprite->GetDC(),
	//	_sprite->GetPos().x,
	//	_sprite->GetPos().y,
	//	_sprite->GetSize().x,
	//	_sprite->GetSize().y,
	//	_sprite->GetTransparent()
	//);
}
