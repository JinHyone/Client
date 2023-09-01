#include "pch.h"
#include "DevScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Actor.h"
#include "Flipbook.h"
#include "SpriteActor.h"
#include "MyPlayer.h"
#include "UI.h"
#include "TileMapActor.h"
#include "TileMap.h"
#include "SoundManager.h"
#include "Sound.h"
#include "Monster.h"
#include "Creature.h"
#include "SceneMananger.h"


DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	GS(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	GS(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
	GS(ResourceManager)->LoadTexture(L"Sword", L"Sprite\\Item\\Sword.bmp");
	GS(ResourceManager)->LoadTexture(L"Arrow", L"Sprite\\Item\\Arrow.bmp", RGB(128, 128, 128));

	GS(ResourceManager)->LoadTexture(L"Potion", L"Sprite\\UI\\Mp.bmp");
	GS(ResourceManager)->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));
	GS(ResourceManager)->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	GS(ResourceManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GS(ResourceManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));
	GS(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp", RGB(255, 255, 255));
	GS(ResourceManager)->LoadTexture(L"Snake", L"Sprite\\Monster\\Snake.bmp", RGB(128, 128, 128));
	GS(ResourceManager)->LoadTexture(L"Hit", L"Sprite\\Effect\\Hit.bmp", RGB(0, 0, 0));

	GS(ResourceManager)->LoadTexture(L"Edit", L"Sprite\\UI\\Edit.bmp", RGB(255, 255, 255));
	GS(ResourceManager)->LoadTexture(L"Exit", L"Sprite\\UI\\Exit.bmp", RGB(255, 255, 255));

	GS(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
	GS(ResourceManager)->CreateSprite(L"TileO", GS(ResourceManager)->GetTexture(L"Tile"), 0, 0, 48, 48);
	GS(ResourceManager)->CreateSprite(L"TileX", GS(ResourceManager)->GetTexture(L"Tile"), 48, 0, 96, 48);
	GS(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
	GS(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);
	GS(ResourceManager)->CreateSprite(L"Edit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 0, 0, 150, 150);
	GS(ResourceManager)->CreateSprite(L"Edit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 150, 0, 150, 150);
	GS(ResourceManager)->CreateSprite(L"Exit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 0, 0, 150, 150);
	GS(ResourceManager)->CreateSprite(L"Exit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 150, 0, 150, 150);

	LoadMap();
	LoadPlayer();;
	LoadMonster();
	LoadProjectile();
	LoadEffect();
	LoadTileMap();

	//GS(ResourceManager)->LoadSound(L"BGM", L"Sound\\BGM.wav");
	//{
	//	Sound* sound = GS(ResourceManager)->GetSound(L"BGM");
	//	sound->Play(true);
	//}

	// GET_SINGLE(ResourceManager)->LoadSound(L"Attack", L"Sound\\Sword.wav");

	Super::Init();
}

void DevScene::Update()
{
	Super::Update();
	float deltaTime = GS(TimeManager)->GetDeltaTime();
	// TickMonsterSpawn();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void DevScene::AddActor(Actor* actor)
{
	Super::AddActor(actor);

	if (actor->GetLayer() == LAYER_OBJECT)
	{
		GameObject* object = dynamic_cast<GameObject*>(actor);

		if (object)
		{
			Tile* tile = _tileMapActor->GetTileMap()->GetTileAt(object->GetCellPos());
			tile->creaturePtr = object;
		}
	}

	Monster* monster = dynamic_cast<Monster*>(actor);
	if (monster) _monsterCount++;
}

void DevScene::RemoveActor(Actor* actor)
{
	Super::RemoveActor(actor);

	GameObject* object = dynamic_cast<GameObject*>(actor);
	if (object)
	{
		if (object->GetLayer() == LAYER_OBJECT)
		{
			Tile* tile = _tileMapActor->GetTileMap()->GetTileAt(object->GetCellPos());
			tile->creaturePtr = nullptr;
		}

		Monster* monster = dynamic_cast<Monster*>(actor);
		if (monster) _monsterCount--;
	}
}

void DevScene::LoadMap()
{
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");
		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		const Vec2Int size = sprite->GetSize();
		background->SetPos(Vec2(size.x / 2, size.y / 2));
		background->SetLayer(LAYER_BACKGROUND);
		AddActor(background);
	}
}

void DevScene::LoadPlayer()
{
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp");
		Flipbook* fbIdle = GS(ResourceManager)->CreateFlipbook(L"FB_IdleUp");
		Flipbook* fbAttack = GS(ResourceManager)->CreateFlipbook(L"FB_AttackUp");
		Flipbook* fbBow = GS(ResourceManager)->CreateFlipbook(L"FB_BowUp");
		Flipbook* fbStaff = GS(ResourceManager)->CreateFlipbook(L"FB_StaffUp");
		fb->SetFlipbookInfo({ texture, L"FB_MoveUp", { 200, 200 }, 0, 9, 1, 0.5f });
		fbIdle->SetFlipbookInfo({ texture, L"FB_IdleUp", { 200, 200 }, 0, 9, 0, 0.5f });
		fbAttack->SetFlipbookInfo({ texture, L"FB_AttackUp" , { 200, 200 }, 0, 7, 3, 0.5f, false });
		fbBow->SetFlipbookInfo({ texture, L"FB_BowUp", { 200, 200 }, 0, 7, 5, 0.5f, false });
		fbStaff->SetFlipbookInfo({ texture, L"FB_StaffUp", { 200, 200 }, 0, 10, 6, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown");
		Flipbook* fbIdle = GS(ResourceManager)->CreateFlipbook(L"FB_IdleDown");
		Flipbook* fbAttack = GS(ResourceManager)->CreateFlipbook(L"FB_AttackDown");
		Flipbook* fbBow = GS(ResourceManager)->CreateFlipbook(L"FB_BowDown");
		Flipbook* fbStaff = GS(ResourceManager)->CreateFlipbook(L"FB_StaffDown");
		fb->SetFlipbookInfo({ texture, L"FB_MoveDown", { 200, 200 }, 0, 9, 1, 0.5f });
		fbIdle->SetFlipbookInfo({ texture, L"FB_IdleDown", { 200, 200 }, 0, 9, 0, 0.5f });
		fbAttack->SetFlipbookInfo({ texture, L"FB_AttackDown" , { 200, 200 }, 0, 7, 3, 0.5f, false });
		fbBow->SetFlipbookInfo({ texture, L"FB_BowDown", { 200, 200 }, 0, 7, 5, 0.5f, false });
		fbStaff->SetFlipbookInfo({ texture, L"FB_StaffDown", { 200, 200 }, 0, 10, 6, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft");
		Flipbook* fbIdle = GS(ResourceManager)->CreateFlipbook(L"FB_IdleLeft");
		Flipbook* fbAttack = GS(ResourceManager)->CreateFlipbook(L"FB_AttackLeft");
		Flipbook* fbBow = GS(ResourceManager)->CreateFlipbook(L"FB_BowLeft");
		Flipbook* fbStaff = GS(ResourceManager)->CreateFlipbook(L"FB_StaffLeft");
		fb->SetFlipbookInfo({ texture, L"FB_MoveLeft", { 200, 200 }, 0, 9, 1, 0.5f });
		fbIdle->SetFlipbookInfo({ texture, L"FB_IdleLeft", { 200, 200 }, 0, 9, 0, 0.5f });
		fbAttack->SetFlipbookInfo({ texture, L"FB_AttackLeft" , { 200, 200 }, 0, 7, 3, 0.5f, false });
		fbBow->SetFlipbookInfo({ texture, L"FB_BowLeft", { 200, 200 }, 0, 7, 5, 0.5f, false });
		fbStaff->SetFlipbookInfo({ texture, L"FB_StaffLeft", { 200, 200 }, 0, 10, 6, 0.5f, false });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight");
		Flipbook* fbIdle = GS(ResourceManager)->CreateFlipbook(L"FB_IdleRight");
		Flipbook* fbAttack = GS(ResourceManager)->CreateFlipbook(L"FB_AttackRight");
		Flipbook* fbBow = GS(ResourceManager)->CreateFlipbook(L"FB_BowRight");
		Flipbook* fbStaff = GS(ResourceManager)->CreateFlipbook(L"FB_StaffRight");
		fb->SetFlipbookInfo({ texture, L"FB_MoveRight", { 200, 200 }, 0, 9, 1, 0.5f });
		fbIdle->SetFlipbookInfo({ texture, L"FB_IdleRight", { 200, 200 }, 0, 9, 0, 0.5f });
		fbAttack->SetFlipbookInfo({ texture, L"FB_AttackRight" , { 200, 200 }, 0, 7, 3, 0.5f, false });
		fbBow->SetFlipbookInfo({ texture, L"FB_BowRight", { 200, 200 }, 0, 7, 5, 0.5f, false });
		fbStaff->SetFlipbookInfo({ texture, L"FB_StaffRight", { 200, 200 }, 0, 10, 6, 0.5f, false });
	}
}

void DevScene::LoadMonster()
{
	{
		Texture* texture = GS(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GS(ResourceManager)->CreateFlipbook(L"FB_SnakeUp");
		fb->SetFlipbookInfo({ texture, L"FB_SnakeUp", { 100, 100 }, 0, 3, 3, 0.5f });
	}
	{
		Texture* texture = GS(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GS(ResourceManager)->CreateFlipbook(L"FB_SnakeDown");
		fb->SetFlipbookInfo({ texture, L"FB_SnakeDown", { 100, 100 }, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GS(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GS(ResourceManager)->CreateFlipbook(L"FB_SnakeLeft");
		fb->SetFlipbookInfo({ texture, L"FB_SnakeLeft", { 100, 100 }, 0, 3, 2, 0.5f });
	}
	{
		Texture* texture = GS(ResourceManager)->GetTexture(L"Snake");
		Flipbook* fb = GS(ResourceManager)->CreateFlipbook(L"FB_SnakeRight");
		fb->SetFlipbookInfo({ texture, L"FB_SnakeRight", { 100, 100 }, 0, 3, 1, 0.5f });
	}
}

void DevScene::LoadProjectile()
{
	{
		Texture* texture = GS(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GS(ResourceManager)->CreateFlipbook(L"FB_ArrowUp");
		fb->SetFlipbookInfo({ texture, L"FB_ArrowUp", { 100, 100 }, 0, 0, 3, 0.5f });
	}
	{
		Texture* texture = GS(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GS(ResourceManager)->CreateFlipbook(L"FB_ArrowDown");
		fb->SetFlipbookInfo({ texture, L"FB_ArrowDown", { 100, 100 }, 0, 0, 0, 0.5f });
	}
	{
		Texture* texture = GS(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GS(ResourceManager)->CreateFlipbook(L"FB_ArrowLeft");
		fb->SetFlipbookInfo({ texture, L"FB_ArrowLeft", { 100, 100 }, 0, 0, 1, 0.5f });
	}
	{
		Texture* texture = GS(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GS(ResourceManager)->CreateFlipbook(L"FB_ArrowRight");
		fb->SetFlipbookInfo({ texture, L"FB_ArrowRight", { 100, 100 }, 0, 0, 2, 0.5f });
	}
}

void DevScene::LoadEffect()
{
	{
		Texture* texture = GS(ResourceManager)->GetTexture(L"Hit");
		Flipbook* fb = GS(ResourceManager)->CreateFlipbook(L"FB_Hit");
		fb->SetFlipbookInfo({ texture, L"FB_Hit", { 50, 47 }, 0, 5, 0, 0.5f, false });
	}
}

void DevScene::LoadTileMap()
{
	{
		TileMapActor* actor = new TileMapActor();
		AddActor(actor);
		_tileMapActor = actor;
		{
			auto* tm = GET_SINGLE(ResourceManager)->CreateTileMap(L"TileMap_01");
			tm->SetMapSize({ 63, 43 });
			tm->SetTileSize(48);

			GS(ResourceManager)->LoadTileMap(L"TileMap_01", L"TileMap\\TileMap_01.txt");

			_tileMapActor->SetTileMap(tm);
			_tileMapActor->SetSHowDebug(false);
			_tileMapActor->SetCanEdit(false);
		}
	}
}

Creature* DevScene::GetCreatureAt(Vec2Int cellPos)
{
	Tile* tile = GS(SceneMananger)->GetTileMapActor()->GetTileMap()->GetTileAt(cellPos);
	return (Creature*)(tile->creaturePtr);
}

void DevScene::Handle_S_AddObject(Protocol::S_AddObject& pkt)
{
	uint64 myPlayerId = GS(SceneMananger)->GetMyPlayerId();
	for (auto& info : pkt.objects())
	{
		if (info.objectid() == myPlayerId) continue;

		if (info.objecttype() == Protocol::OBJECT_TYPE_PLAYER)
		{
			Player* player = SpawnObject<Player>(Vec2Int(info.posx(), info.posy()));
			player->SetDir(info.dir());
			player->SetState(info.state());
			player->info = info;
		}
		else if (info.objecttype() == Protocol::OBJECT_TYPE_MONSTER)
		{
			Monster* monster = SpawnObject<Monster>(Vec2Int(info.posx(), info.posy()));
			monster->SetDir(info.dir());
			monster->SetState(info.state());
			monster->info = info;
		}
	}
}

void DevScene::Handle_S_RemoveObject(Protocol::S_RemoveObject& pkt)
{
	for (uint64 id : pkt.ids())
	{
		GameObject* gameObject = GetObject(id);
		if (gameObject) RemoveActor(gameObject);
	}
}

GameObject* DevScene::GetObject(uint64 id)
{
	for (Actor* actor : _actors[LAYER_OBJECT])
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(actor);
		if (gameObject)
		{
			if (gameObject->GetObjectID() == id)
				return gameObject;
		}
	}

	return nullptr;
}

Player* DevScene::FindClosestPlayer(Vec2Int cellPos)
{
	float best = FLT_MAX;
	Player* ret = nullptr;

	for (Actor* actor : _actors[LAYER_OBJECT])
	{
		Player* player = dynamic_cast<Player*>(actor);
		if (player)
		{
			Vec2Int dir = player->GetCellPos() - cellPos;
			float dist = dir.LengthSquared();

			if (dist < best)
			{
				best = dist;
				ret = player;
			}
		}
	}

	return ret;
}

bool DevScene::FindPath(Vec2Int src, Vec2Int dest, vector<Vec2Int>& path, int32 maxDepth)
{
	int32 depth = abs(dest.y - src.y) + abs(dest.x - src.x);
	if (depth >= maxDepth) return false;

	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
	map<Vec2Int, int32> best;
	map<Vec2Int, Vec2Int> parent;

	// 초기 값
	{
		int32 cost = abs(dest.y - src.y) + abs(dest.x - src.x);
		pq.push(PQNode(cost, src));
		best[src] = cost;
		parent[src] = src;
	}

	Vec2Int front[4] =
	{
		{ 0, -1 }, // UP
		{ 0, 1 }, // DOWN
		{ -1, 0}, // RIGHT
		{ 1, 0 }, // LEFT
	};

	bool found = false;
	while (!pq.empty())
	{
		// 제일 좋은 후보를 찾는다.
		PQNode now = pq.top();
		pq.pop();

		// 더 짧은 경로를 뒤늦게 찾았다면 스킵
		if (best[now.pos] < now.cost) continue;
		if (now.pos == dest)
		{
			found == true;
			break;
		}

		// 방문
		for (int32 dir = 0; dir < 4; dir++)
		{
			Vec2Int nextPos = now.pos + front[dir];

			if (CanGo(nextPos) == false) continue;

			int32 depth = abs(nextPos.y - src.y) + abs(nextPos.x - src.x);
			if (depth >= maxDepth) continue;

			// 가중치 계산
			int32 cost = abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x);
			int32 bestCost = best[nextPos];

			if (bestCost != 0)
			{
				if (bestCost <= cost) continue;
			}

			pq.push(PQNode(cost, nextPos));

			best[nextPos] = cost;
			parent[nextPos] = now.pos;
		}
	}

	if (found == false)
	{
		// TODO
		float bestScore = FLT_MAX;

		for (auto& item : best)
		{
			Vec2Int pos = item.first;
			int32 score = item.second;

			if (bestScore == score)
			{
				int32 dist1 = abs(dest.x - src.x) + abs(dest.y - src.y);
				int32 dist2 = abs(pos.x - src.x) + abs(pos.y - src.y);

				if (dist1 > dist2) dest = pos;
			}

			else if (bestScore > score)
			{
				dest = pos;
				bestScore = score;
			}
		}
	}

	path.clear();
	Vec2Int pos = dest;

	while (parent[pos] != pos)
	{
		path.push_back(pos);
		pos = parent[pos];
	}

	std::reverse(path.begin(), path.end());
	return true;
}

bool DevScene::CanGo(Vec2Int cellPos)
{
	if (_tileMapActor == nullptr) return false;

	TileMap* tm = _tileMapActor->GetTileMap();
	if (tm == nullptr) return false;

	Tile* tile = tm->GetTileAt(cellPos);
	if (tile == nullptr) return false;
	if (tile->value == 1) return false;
	if (tile->creaturePtr != nullptr) return false;

	return true;
}

Vec2 DevScene::ConvertPos(Vec2Int cellPos)
{
	Vec2 ret = {0, 0};

	if (_tileMapActor == nullptr)
		return ret;

	TileMap* tm = _tileMapActor->GetTileMap();
	if (tm == nullptr)
		return ret;

	int32 size = tm->GetTileSize();
	Vec2 pos = _tileMapActor->GetPos();

	ret.x = pos.x + cellPos.x * size + ((float)size / 2);
	ret.y = pos.y + cellPos.y * size + ((float)size / 2);

	return ret;
}

Vec2Int DevScene::GetRandomEmptyCellPos()
{
	Vec2Int ret = { -1, -1 };

	if (_tileMapActor == nullptr) return ret;
	
	TileMap* tm = _tileMapActor->GetTileMap();
	if (tm == nullptr) return ret;

	Vec2Int size = tm->GetMapSize();

	while (true)
	{
		int32 x = rand() % size.x;
		int32 y = rand() % size.y;
		Vec2Int cellPos{ x, y };

		if (CanGo(cellPos)) return cellPos;
	}
}

void DevScene::TickMonsterSpawn()
{
	if (_monsterCount < DESIRED_MONSTER_COUNT) SpawnObjectAtRandomPos<Monster>();
}
