#pragma once

class Scene;
class TileMapActor;
class MyPlayer;
class DevScene;

class SceneMananger
{
	GNERATE_SINGLE(SceneMananger);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

public:
	void ChangeScene(SceneType scenetype);
	Scene* GetCurrentScene() { return _scene; }

	DevScene* GetDevScene();

	MyPlayer* GetMyPlayer() { return _myPlayer; }
	void SetMyPlayer(MyPlayer* myPlayer) { _myPlayer = myPlayer; }

	uint64 GetMyPlayerId();

private:
	Scene* _scene = nullptr;
	SceneType _sceneType = SceneType::None;
	MyPlayer* _myPlayer = nullptr;

public:
	Vec2 GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vec2 pos) { _cameraPos = pos; }

public:
	TileMapActor* GetTileMapActor();

private:
	Vec2 _cameraPos = { 400, 400 };
};

