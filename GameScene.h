#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
};

