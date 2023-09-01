#include "pch.h"
#include "Scene.h"
#include "TimeManager.h"
#include "Actor.h"
#include "UI.h"
#include "Sprite.h"
#include "ResourceManager.h"

Scene::Scene()
{
	for (const vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Init();

	for (UI* ui : _uis)
		ui->Init();
}

Scene::~Scene()
{
}

void Scene::Init()
{

}

void Scene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->Update();
		}
	}

	for (UI* ui : _uis)
	{
		ui->Update();
	}
}

void Scene::Render(HDC hdc)
{
	vector<Actor*>& actors = _actors[LAYER_OBJECT];
	std::sort(actors.begin(), actors.end(), [=](Actor* a, Actor* b)
		{
			return a->GetPos().y < b->GetPos().y;
		});

	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->Render(hdc);
		}
	}

	for (UI* ui : _uis)
	{
		ui->Render(hdc);
	}
}

void Scene::AddActor(Actor* actor)
{
	if (actor == nullptr) return;
	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr) return;
	vector<Actor*>& v = _actors[actor->GetLayer()];
	v.erase(std::remove(v.begin(), v.end(), actor), v.end());
}
