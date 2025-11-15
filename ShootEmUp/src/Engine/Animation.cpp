#include "pch.h"
#include "Animation.h"
#include "AssetManager.h"
#include "AnimationManager.h"
#include "GameManager.h"

void Animation::PlayAnimation(Sprite* sprite)
{
	sprite->ResizeTexture(m_animationsFrames[0]);
	sprite->SetSpriteWidthAndHeight(m_animationsFrames[0]->m_width, m_animationsFrames[0]->m_height);
}

bool Animation::Update(int* currentFrame, float* currentFrameTime, Sprite* sprite)
{
	*currentFrameTime += GameManager::Get()->GetDeltaTime();


	if (*currentFrameTime >= m_displaySpeed) {
		*currentFrameTime -= m_displaySpeed; 
		*currentFrame += 1; 
		if (*currentFrame == m_animationsFrames.size())
		{
			if (m_isLooping == false)
				return false;

			*currentFrame = 0;
		}
		sprite->ResizeTexture(m_animationsFrames[*currentFrame]);
	}
	return true; 
}
