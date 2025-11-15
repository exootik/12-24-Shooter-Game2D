#pragma once

#include <map>
#include <string>

#include "pch.h"

class GameManager;
class WindowRender;
class Sprite;

class GCGraphics;
class GCTexture;

template <typename Resource>
struct RessourcesResult {
	bool success;
	Resource* resource;
};

struct Frames
{
	int m_idInSpriteSheet;
	float m_width, m_height;
	float m_startX, m_startY;
	Vect2 uvsPos[4];
	std::string m_name;
};

struct SpriteSheet
{
	const char* m_fileName;
	float m_width, m_height;
	int m_rows, m_columns, m_frameNumber;

	std::vector<Frames*> m_frames;

	Sprite* m_spritesheetSprite;
};


struct Texture 
{
	sf::Texture m_sfmlTexture;
	GCTexture* m_pGCTexture;
};

struct Font
{
	sf::Font m_sfFont; 
	GCTexture* m_GCfontTexture;
};

struct Atlas
{
	int m_textureCount;
	float m_width, m_height;

	Texture* m_pTexture;

	std::map<std::string, Frames*> m_assests;
};



class AssetManager
{
public:


	static AssetManager* Get();

	static RessourcesResult<Atlas> LoadAtlas(const char* filename);
	static RessourcesResult<Atlas> GetAtlas(const char* filename);
	static RessourcesResult<Frames> GetAtlasAsset(const char* atlasName, const char* assetName);

	static RessourcesResult<Font> LoadFont(const char* filename);
	static RessourcesResult<Font> GetFont(const char* filename);

	static RessourcesResult<Texture> LoadTexture(const char* filename);
	static RessourcesResult<Texture> GetTexture(const char* filename);

	static RessourcesResult<SpriteSheet> LoadSpriteSheet(const char* fileName, int frameNumber, float SpriteSheetWidth, float SpriteSheetHeight, int rows, int columns);
	static RessourcesResult<SpriteSheet> GetSpriteSheet(const char* fileName);

	static RessourcesResult<Sprite> GetSprite(const char* spriteName);

protected:
	enum AssetType
	{
		SFML, GCRENDER
	};
	static void CutSpriteSheet(SpriteSheet* spritesheet);

	static void SetType(AssetType type) { AssetManager::Get()->m_assetType = type; }
	static AssetType GetType() { return AssetManager::Get()->m_assetType; }

	static void SetGCGraphics(GCGraphics* pGraphics) { AssetManager::Get()->m_pGraphics = pGraphics; }

protected:
	AssetType m_assetType;
	GCGraphics* m_pGraphics;
	std::map<const char*, Font*> m_fonts;
	
	std::map<std::string, Texture*> m_textures;
	std::map<std::string, SpriteSheet*> m_spritesheet;
	std::map<std::string, Atlas*> m_atlas;
	std::map<std::string, Sprite*> m_sprites;

	friend GameManager;
	friend WindowRender;
};

