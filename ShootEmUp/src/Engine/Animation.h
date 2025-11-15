#pragma once



class Frames;
#include "Sprite.h"

class Animation
{
public: 
	void PlayAnimation(Sprite* sprite);
	bool Update(int* currentFrame,float* currentFrameTime, Sprite* sprite);
	void SetLooping(bool loop) { m_isLooping = loop; }
	Sprite* GetSprite() { return m_pSprite->Duplicate(); }

	void SetSpeed(float speed) { m_displaySpeed = speed; }
protected:
	const char* m_spritesheetName;
	const char* m_animationName;
	float m_displaySpeed;
	std::vector<Frames*> m_animationsFrames;
	bool m_isLooping;

	Sprite* m_pSprite;

private: 
	Animation(const char* name, const char* spritesheetName) : m_animationName(name), m_spritesheetName(spritesheetName), m_isLooping(true),m_displaySpeed(0.05f) {};
	~Animation() {};

	friend class AnimationManager;
};

