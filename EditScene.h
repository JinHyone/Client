#pragma once
#include "Scene.h"

class EditScene : public Scene
{
public:
	EditScene();
	virtual ~EditScene() override;

public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;

private:
	vector<pair<POINT, POINT>> _lines;
	bool _setOrigin = true;
	POINT _lastPos = {};
};

