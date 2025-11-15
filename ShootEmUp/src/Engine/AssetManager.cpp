#include "pch.h"
#include "AssetManager.h"
#include "Sprite.h"
#include "SpriteSFML.h"
#include "SpriteRender.h"
#include "GameManager.h"

#include "Render.h"

#include <fstream>
#include "json.hpp"

using json = nlohmann::json;


AssetManager* AssetManager::Get()
{
	static AssetManager mInstance;

	return &mInstance;
}

RessourcesResult<Atlas> AssetManager::LoadAtlas(const char* filename)
{
	RessourcesResult<Atlas> result = {false, nullptr};
	AssetManager* pInstance = AssetManager::Get();
	
	if (pInstance->LoadTexture(filename).success == false)
	{
		std::cerr << "Texture Atlas Not Found" << std::endl;
		return result;
	}

	std::string jsonFilepath = "../../res/Engine/";
	jsonFilepath += filename;
	jsonFilepath += ".json";
	std::ifstream jsonFile(jsonFilepath);
	json atlasData = json::parse(jsonFile);

	result.resource = new Atlas();
	result.resource->m_textureCount = atlasData["TexturesCount"];
	result.resource->m_width = atlasData["width"];
	result.resource->m_height = atlasData["height"];

	for (auto it = atlasData["Textures"].begin(); it != atlasData["Textures"].end(); it++)
	{
		Frames* pAsset = new Frames();
		pAsset->m_startX = it.value()["x"];
		pAsset->m_startY = it.value()["y"];
		pAsset->m_width = it.value()["w"];
		pAsset->m_height = it.value()["h"];
		pAsset->m_name = it.value()["name"];
		pAsset->uvsPos[0] = Vect2(pAsset->m_startX, pAsset->m_startY + pAsset->m_height);//Bottom-Left
		pAsset->uvsPos[1] = Vect2(pAsset->m_startX, pAsset->m_startY);//Top-Left
		pAsset->uvsPos[2] = Vect2(pAsset->m_startX + pAsset->m_width, pAsset->m_startY);//Top-Right
		pAsset->uvsPos[3] = Vect2(pAsset->m_startX + pAsset->m_width, pAsset->m_startY + pAsset->m_height);//Bottom-Right

		result.resource->m_assests.insert(std::pair<std::string, Frames*>(pAsset->m_name, pAsset));
	}

	pInstance->m_atlas.insert(std::pair<const char*, Atlas*>(filename, result.resource));

	for (auto it = result.resource->m_assests.begin(); it != result.resource->m_assests.end(); ++it )
	{
		Sprite* pSprite = GameManager::Get()->GetWindow()->CreateSpriteWithAtlas(filename, it->second->m_name.c_str());
		pInstance->m_sprites.insert(std::pair<const char*, Sprite*>(it->second->m_name.c_str(), pSprite));
	}
	return result;
}

RessourcesResult<Atlas> AssetManager::GetAtlas(const char* filename)
{
	AssetManager* pInstance = AssetManager::Get();
	RessourcesResult<Atlas> res = { false, nullptr };
	if (pInstance->m_fonts.find(filename) == pInstance->m_fonts.end())
	{
		res.success = false;
		std::cout << "Atlas not Found";
		return res;
	}
	res.success = true;
	res.resource = pInstance->m_atlas[filename];
	return res;
}

RessourcesResult<Frames> AssetManager::GetAtlasAsset(const char* atlasName, const char* assetName)
{
	AssetManager* pInstance = AssetManager::Get();
	RessourcesResult<Frames> res = { false, nullptr };
	Atlas* pAtlas = nullptr;
	if (pInstance->m_atlas.find(atlasName) == pInstance->m_atlas.end())
	{
		res.success = false;
		std::cout << "Atlas not Found";
		return res;
	}
	pAtlas = pInstance->m_atlas[atlasName];

	if (pAtlas->m_assests.find(assetName) == pAtlas->m_assests.end())
	{
		res.success = false;
		std::cout << "Asset not Found";
		return res;
	}
	res.success = true;
	res.resource = pAtlas->m_assests[assetName];
	return res;
}


RessourcesResult<Font> AssetManager::LoadFont(const char* filename)
{
	RessourcesResult<Font> result = { false, nullptr };
	AssetManager* pInstance = AssetManager::Get();

	if (pInstance->m_fonts.find(filename) != pInstance->m_fonts.end())
	{
		std::cout << "Font already loaded";
		return result;
	}
	std::string filepath = "../../res/Fonts/";
	filepath += filename;

	result.resource = new Font();

	switch (pInstance->GetType())
	{
	case AssetType::SFML:
		result.success = result.resource->m_sfFont.loadFromFile(filepath);
		break;
	case AssetType::GCRENDER:
		filepath += ".dds";
		GCGraphics* pgraphics = pInstance->m_pGraphics;
		pgraphics->InitializeGraphicsResourcesStart();
		GC_RESOURCE_CREATION_RESULT<GCTexture*> pres = pgraphics->CreateTexture(filepath);
		pgraphics->InitializeGraphicsResourcesEnd();

		result.resource->m_GCfontTexture = pres.resource;
		result.success = pres.success;
		break;
	}

	_ASSERT(result.success);

	if (result.success == false)
	{
		result.resource = nullptr;
		return result;
	}

	pInstance->m_fonts.insert(std::pair<const char*,Font*>(filename, result.resource));
	return result;
}


RessourcesResult<Font> AssetManager::GetFont(const char* filename)
{
	AssetManager* pInstance = AssetManager::Get();
	RessourcesResult<Font> res = { false, nullptr  };
	if (pInstance->m_fonts.find(filename) == pInstance->m_fonts.end())
	{
		res.success = false;
		std::cout << "Font not Found";
		return res;
	}
	res.success = true; 
	res.resource = pInstance->m_fonts[filename];
	return res;
}


RessourcesResult<Texture> AssetManager::LoadTexture(const char* filename)
{
	RessourcesResult<Texture> result{false, nullptr};
	AssetManager* pInstance = AssetManager::Get();

	if (pInstance->m_textures.find(filename) != pInstance->m_textures.end())
	{
		std::cout << "Texture already loaded";
		return result;
	}
	std::string filepath = "../../res/Textures/";
	filepath += filename;

	result.resource = new Texture();
	
	switch (pInstance->GetType())
	{
	case AssetType::SFML:
		filepath += ".png";
		result.success = result.resource->m_sfmlTexture.loadFromFile(filepath);
		break;
	case AssetType::GCRENDER:
		filepath += ".dds";
		GCGraphics* pgraphics = pInstance->m_pGraphics;
		pgraphics->InitializeGraphicsResourcesStart();
		GC_RESOURCE_CREATION_RESULT<GCTexture*> pres = pgraphics->CreateTexture(filepath);
		pgraphics->InitializeGraphicsResourcesEnd();

		result.resource->m_pGCTexture = pres.resource;
		result.success = pres.success;
		break;
	}

	_ASSERT(result.success);

	if (result.success == false)
	{
		result.resource = nullptr;
		return result;
	}

	pInstance->m_textures.insert(std::pair<const char*, Texture*>(filename, result.resource));
	return result;
}

RessourcesResult<Texture> AssetManager::GetTexture(const char* filename)
{
	AssetManager* pInstance = AssetManager::Get();
	RessourcesResult<Texture> res = { false, nullptr };

	if (pInstance->m_textures.find(filename) == pInstance->m_textures.end())
	{
		res.success = false;
		std::cout << "Texture not Found";
		return res;
	}
	res.success = true;
	res.resource = pInstance->m_textures[filename];
	return res;
}

RessourcesResult<SpriteSheet> AssetManager::LoadSpriteSheet(const char* fileName, int frameNumber, float SpriteSheetWidth, float SpriteSheetHeight, int rows, int columns)
{
	RessourcesResult<SpriteSheet> result = {false, nullptr};
	AssetManager* pInstance = AssetManager::Get();

	if (pInstance->m_spritesheet.find(fileName) != pInstance->m_spritesheet.end())
	{
		std::cout << "SprietSheet already loaded";
		return result;
	}

	std::string filepath = "../../res/Textures/";
	filepath += fileName;

	RessourcesResult<Texture> textResult = { false, nullptr };


	switch (pInstance->GetType())
	{
	case AssetType::SFML:
		textResult = AssetManager::LoadTexture(fileName);
		break;
	case AssetType::GCRENDER:
		textResult = AssetManager::LoadTexture(fileName);
		break;
	}

	_ASSERT(textResult.success);

	if (textResult.success == false)
		return result;

	result.success = true;
	result.resource = new SpriteSheet();
	result.resource->m_fileName = fileName;
	result.resource->m_frameNumber = frameNumber;
	result.resource->m_width = SpriteSheetWidth;
	result.resource->m_height = SpriteSheetHeight;
	result.resource->m_rows = rows;
	result.resource->m_columns = columns;
	pInstance->CutSpriteSheet(result.resource);

	switch (pInstance->m_assetType)
	{
	case AssetManager::SFML:
		result.resource->m_spritesheetSprite = new SpriteSFML();
		break;
	case AssetManager::GCRENDER:
		result.resource->m_spritesheetSprite = new SpriteRender(AssetManager::Get()->m_pGraphics);
		break;
	}
	result.resource->m_spritesheetSprite->SetTexture(fileName);


	pInstance->m_spritesheet.insert(std::pair<const char*, SpriteSheet*>(fileName, result.resource));
	return result;
}

RessourcesResult<SpriteSheet> AssetManager::GetSpriteSheet(const char* fileName)
{
	AssetManager* pInstance = AssetManager::Get();
	RessourcesResult<SpriteSheet> res = { false, nullptr };

	if (pInstance->m_spritesheet.find(fileName) == pInstance->m_spritesheet.end())
	{
		res.success = false;
		std::cout << "Texture not Found";
		return res;
	}
	res.success = true;
	res.resource = pInstance->m_spritesheet[fileName];
	return res;
}

RessourcesResult<Sprite> AssetManager::GetSprite(const char* spriteName)
{
	AssetManager* pInstance = AssetManager::Get();
	RessourcesResult<Sprite> res = { false, nullptr };

	if (pInstance->m_sprites.find(spriteName) == pInstance->m_sprites.end())
	{
		res.success = false;
		std::cout << "Sprite not Found";
		return res;
	}
	res.success = true;
	res.resource = pInstance->m_sprites[spriteName]->Duplicate();
	return res;
}

void AssetManager::CutSpriteSheet(SpriteSheet* spritesheet)
{
	int spritesID = 0;
	float spritesWidth = spritesheet->m_width / spritesheet->m_columns;
	float spritesHeight = spritesheet->m_height/ spritesheet->m_rows;

	float X, Y = 0;

	for (int i = 0; i < spritesheet->m_rows; i++ )
	{
		X = 0;
		for (int i = 0; i < spritesheet->m_columns; i++)
		{
			Frames* sprite = new Frames(); 
			sprite->m_width = spritesWidth;
			sprite->m_height = spritesHeight;
			sprite->m_idInSpriteSheet = spritesID++;
			sprite->m_startX = X;
			sprite->m_startY = Y;
			sprite->uvsPos[0] = Vect2(X, Y + spritesHeight);//Bottom-Left
			sprite->uvsPos[1] = Vect2(X, Y );//Top-Left
			sprite->uvsPos[2] = Vect2(X + spritesWidth, Y );//Top-Right
			sprite->uvsPos[3] = Vect2(X + spritesWidth, Y + spritesHeight);//Bottom-Right
			X += spritesWidth;
			spritesheet->m_frames.push_back(sprite);
		}
		Y += spritesHeight;
	};
}