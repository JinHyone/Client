#include "pch.h"
#include "Actor.h"
#include "Compoent.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Init()
{
	for (Compoent* compoent : _compoents)
	{
		compoent->Init();
	}
}

void Actor::Update()
{
	for (Compoent* compoent : _compoents)
	{
		compoent->Update();
	}
}

void Actor::Render(HDC hdc)
{
	for (Compoent* compoent : _compoents)
	{
		compoent->Render(hdc);
	}
}

void Actor::AddCompoent(Compoent* compoent)
{
	if (compoent == nullptr) return;
	compoent->SetOwner(this);
	_compoents.push_back(compoent);
}

void Actor::RemoveCompoent(Compoent* compoent)
{
	auto findIt = ::find(_compoents.begin(), _compoents.end(), compoent);
	if (findIt == _compoents.end()) return;

	_compoents.erase(findIt);
}

void Actor::OnCollisionEnter(Collider* src, Collider* dest)
{
}

void Actor::OnCollisionExit(Collider* src, Collider* dest)
{
}
