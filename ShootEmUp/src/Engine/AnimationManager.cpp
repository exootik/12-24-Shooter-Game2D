#include "pch.h"
#include "AnimationManager.h"
#include "Animation.h"
#include "AssetManager.h"

AnimationManager* AnimationManager::Get()
{
	static AnimationManager mInstance;

	return &mInstance;
}

RessourcesResult<Animation> AnimationManager::CreateAnimation(const char* animationName, const char* spritesheetName, int firstframe, int frameNumber)
{
	RessourcesResult<Animation> result  = { false, nullptr};
	AnimationManager* pInstance = AnimationManager::Get();

	if (pInstance->m_animationList.find(animationName) != pInstance->m_animationList.end())
	{
		std::cout << "Animation already exists" << std::endl;
		return result;
	}

	if (AssetManager::Get()->GetSpriteSheet(spritesheetName).success == false) {
		std::cout << "SpriteSheet Unknow" << std::endl;
		return result;
	}
	SpriteSheet* spritesheet = AssetManager::Get()->GetSpriteSheet(spritesheetName).resource;
	result.resource = new Animation(animationName,spritesheetName);
	result.resource->m_pSprite = spritesheet->m_spritesheetSprite;

	for (int i = firstframe; i < firstframe + frameNumber; i++)
	{
		result.resource->m_animationsFrames.push_back(spritesheet->m_frames[i]);
	}

	pInstance->m_animationList.insert(std::pair<const char*, Animation*>(animationName, result.resource));
	return result;
}

bool AnimationManager::PlayAnimation(const char* animationName, Sprite* pSprite)
{
	AnimationManager* pInstance = AnimationManager::Get();

	if (pInstance->m_animationList.find(animationName) == pInstance->m_animationList.end())
	{
		std::cout << "Animation not created" << std::endl;
		return false;
	}

	pInstance->m_animationList[animationName]->PlayAnimation(pSprite);
	return true;
}

RessourcesResult<Animation> AnimationManager::GetAnimation(const char* animationName)
{
	AnimationManager* pInstance = AnimationManager::Get();
	RessourcesResult<Animation> res = { false, nullptr };
	if (pInstance->m_animationList.find(animationName) == pInstance->m_animationList.end())
	{
		std::cout << "Animation Not Found";
		return res;
	}
	res.success = true;
	res.resource = pInstance->m_animationList[animationName];
	return res;
}

//bool AnimationManager::StopAnimation(const char* animationName)
//{
//	AnimationManager* pInstance = AnimationManager::Get();
//
//	if (pInstance->m_animationList.find(animationName) == pInstance->m_animationList.end())
//	{
//		std::cout << "Animation not created" << std::endl;
//		return false;
//	}
//
//	pInstance->m_animationList[animationName]->StopAnimation();
//	return true;
//}
