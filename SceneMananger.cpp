#include "pch.h"
#include "SceneMananger.h"
#include "DevScene.h"
#include "GameScene.h"
#include "EditScene.h"
#include "TileMapActor.h"
#include "MyPlayer.h"


SceneMananger* SceneMananger::s_instance = nullptr;

void SceneMananger::Init()
{
}

void SceneMananger::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneMananger::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
}

void SceneMananger::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneMananger::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType) return;

	Scene* newScene = nullptr;
	
	switch (sceneType)
	{
		case SceneType::DevScene:
			newScene = new DevScene();
			break;
		case SceneType::GameScene:
			newScene = new GameScene();
			break;
		case SceneType::EditScene:
			newScene = new EditScene();
			break;
	}

	SAFE_DELETE(_scene);

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}

DevScene* SceneMananger::GetDevScene()
{
	return dynamic_cast<DevScene*>(GetCurrentScene());
}

uint64 SceneMananger::GetMyPlayerId()
{
	return _myPlayer ? _myPlayer->GetObjectID() : 0;
}

TileMapActor* SceneMananger::GetTileMapActor()
{
	DevScene* devScene = dynamic_cast<DevScene*>(_scene);

	if (devScene == nullptr) return nullptr;
	return devScene->_tileMapActor;
}
