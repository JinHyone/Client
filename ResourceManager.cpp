#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "TileMap.h"
#include "Sound.h"

ResourceManager* ResourceManager::s_instance = nullptr;

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;
}

void ResourceManager::Clear()
{
	for (auto& item : _textures) SAFE_DELETE(item.second);
	_textures.clear();

	for (auto& item : _sprites) SAFE_DELETE(item.second);
	_sprites.clear();
	
	for (auto& item : _flipbooks) SAFE_DELETE(item.second);
	_flipbooks.clear();

	for (auto& item : _tileMaps) SAFE_DELETE(item.second);
	_tileMaps.clear();
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
	if (_textures.find(key) != _textures.end()) return _textures[key];
	fs::path fullPath = _resourcePath / path;

	Texture* texture = new Texture();
	texture->LoadBmp(_hwnd, fullPath.c_str());
	texture->SetTransparent(transparent);
	_textures[key] = texture;
	return texture;
}

Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];

	if (cx == 0)
		cx = texture->GetSize().x;

	if (cy == 0)
		cy = texture->GetSize().y;

	Sprite* sprite = new Sprite(texture, x, y, cx, cy);
	_sprites[key] = sprite;

	return sprite;
}

Flipbook* ResourceManager::CreateFlipbook(const wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end())
		return _flipbooks[key];

	Flipbook* fb = new Flipbook();
	_flipbooks[key] = fb;
	
	return fb;
}

TileMap* ResourceManager::CreateTileMap(const wstring& key)
{
	if (_tileMaps.find(key) != _tileMaps.end()) return _tileMaps[key];

	TileMap* tm = new TileMap();
	_tileMaps[key] = tm;

	return tm;
}

void ResourceManager::SaveTileMap(const wstring& key, const wstring& path)
{
	TileMap* tm = GetTileMap(key);

	fs::path fullPath = _resourcePath / path;
	tm->SaveFile(fullPath);
}

TileMap* ResourceManager::LoadTileMap(const wstring& key ,const wstring& path)
{
	TileMap* tm = nullptr;
	if (_tileMaps.find(key) == _tileMaps.end())
		_tileMaps[key] = new TileMap();

	tm = _tileMaps[key];

	fs::path fullPath = _resourcePath / path;
	tm->LoadFile(fullPath);

	return tm;
}

Sound* ResourceManager::LoadSound(const wstring& key, const wstring& path)
{
	if (_sounds.find(key) != _sounds.end()) return _sounds[key];
	fs::path fullPath = _resourcePath / path;

	Sound* sound = new Sound();
	sound->LoadWave(fullPath);
	_sounds[key] = sound;

	return sound;
}
