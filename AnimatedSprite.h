#pragma once
#include "Sprite.h"
class AnimatedSprite : public Sprite
{
protected:
	int m_currentSpriteIndex;
	int m_maxSprite;
	float m_currentTime;
	float m_frameRate;

public:
	AnimatedSprite(int angle, float frameRate, int maxSprite, SDL_Rect sourceTransform, SDL_FRect destinationTransform);
	void Animate(float deltaTime);
};

