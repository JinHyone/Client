#pragma once
#include "Actor.h"

class Compoent
{
public:
	Compoent();
	virtual ~Compoent();

	virtual void Init() {  };
	virtual void Update() {  };
	virtual void Render(HDC hdc) {  }

	void SetOwner(Actor* owner) { _owner = owner; }
	Actor* GetOwner() { return _owner; }

protected:
	Actor* _owner;
};

