#pragma once
#include "Animation.h"
#include "AssetManager.h"

class AnimationManager
{
public :

	static AnimationManager* Get();

	static RessourcesResult<Animation> CreateAnimation(const char* animationName, const char* spritesheetName, int firstframe, int frameNumber);
	static bool PlayAnimation(const char* animationName, Sprite* pSprite);
	static RessourcesResult<Animation> GetAnimation(const char* animationName);
	//static bool StopAnimation(const char* animationName);

protected:

	std::map<const char*,Animation*> m_animationList;
};

