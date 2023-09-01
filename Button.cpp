#include "pch.h"
#include "Button.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneMananger.h"
#include "Sprite.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Init()
{
	Super::Init();

	SetButtonState(BS_Defalut);

	AddOnClickDelegate(this, &Button::OnClickButton);
}

void Button::Update()
{
	Super::Update();

	POINT mousePos = GS(InputManager)->GetMousePos();
	float deltaTime = GS(TimeManager)->GetDeltaTime();

	if (_state == BS_Clicked)
	{
		_sumTime += deltaTime;
		if (_sumTime >= 0.2f)
		{
			_sumTime = 0;
			SetButtonState(BS_Defalut);
		}
	}

	if (IsMouseInRect())
	{
		if (GS(InputManager)->GetButton(KeyType::LeftMouse))
		{
			SetButtonState(BS_Pressed);
			// OnPressed
		}
		else
		{
			if (_state == BS_Pressed)
			{
				SetButtonState(BS_Clicked);
				// OnClicked
				if (_onClick) _onClick();
			}
		}
	}
	else
	{
		SetButtonState(BS_Defalut);
	}
}

void Button::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2 CameraPos = GS(SceneMananger)->GetCameraPos();

	if (_currentSprite != nullptr)
	{
		TransparentBlt
		(
			hdc,
			_pos.x - _size.x / 2 - (CameraPos.x - GWinSizeX / 2),
			_pos.y - _size.y / 2 - (CameraPos.y - GWinSizeY / 2),
			_size.x,
			_size.y,
			_currentSprite->GetDC(),
			_currentSprite->GetPos().x,
			_currentSprite->GetPos().y,
			_currentSprite->GetSize().x,
			_currentSprite->GetSize().y,
			_currentSprite->GetTransparent()
		);
	}
	else
	{
		Vec2 cameraPos = GS(SceneMananger)->GetCameraPos();
		Vec2 rect =
		{
			_pos.x - (CameraPos.x - GWinSizeX / 2),
			_pos.y - (CameraPos.y - GWinSizeY / 2)
		};

		Utils::DrawRect(hdc, rect, _size.x, _size.y);
	}

}

void Button::SetButtonState(ButtonState state)
{
	_state = state;

	if (_sprites[state])
		SetCurrentSprite(_sprites[state]);
}
