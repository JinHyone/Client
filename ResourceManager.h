#pragma once

class Texture;
class ResourceBase;
class Sprite;
class Flipbook;
class TileMap;
class Sound;

class ResourceManager
{
	GNERATE_SINGLE(ResourceManager);
	~ResourceManager();

public:
	void Init(HWND hwnd, fs::path resourcePath);
	void Clear();

	const fs::path& GetRosourcePath() { return _resourcePath; }

	Texture* GetTexture(const wstring& key) { return _textures[key]; }
	Texture* LoadTexture(const wstring& key, const wstring& path, uint32 transparent = RGB(255, 0, 255));

	Sprite* GetSprite(const wstring& key) { return _sprites[key]; }
	Sprite* CreateSprite(const wstring& key, Texture* texture, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);

	Flipbook* GetFlipbook(const wstring& key) { return _flipbooks[key]; }
	Flipbook* CreateFlipbook(const wstring& key);

	TileMap* GetTileMap(const wstring& key) { return _tileMaps[key]; }
	TileMap* CreateTileMap(const wstring& key);

	void SaveTileMap(const wstring& key, const wstring& path);
	TileMap* LoadTileMap(const wstring& key, const wstring& path);


	Sound* GetSound(const wstring& key) { return _sounds[key]; }
	Sound* LoadSound(const wstring& key, const wstring& path);

private:
	HWND _hwnd;
	fs::path _resourcePath;
	unordered_map<wstring, Texture*> _textures;
	unordered_map<wstring, Sprite*>	 _sprites;
	unordered_map<wstring, Flipbook*> _flipbooks;
	unordered_map<wstring, TileMap*> _tileMaps;
	unordered_map<wstring, Sound*> _sounds;
};