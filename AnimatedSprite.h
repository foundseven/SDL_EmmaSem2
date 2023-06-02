#pragma once
#include "Sprite.h"
class AnimatedSpriteObject : public SpriteObject
{
public:
	//virtual void Render() = 0;
	//virtual?
	void Update(float deltaTime) override;
	AnimatedSpriteObject(int angle, float frameRate, int maxSprites, SDL_Rect sourceTransform, SDL_FRect destinationTransform);

protected:
	int m_currentSpriteIndex;
	int m_startingSpriteIndex;
	int m_totalSprite;
	int m_maxSprites;


	float m_currentTime;
	float m_frameRate;

protected:
	//AnimatedSpriteObject(const SDL_Rect source, const SDL_FRect destination);

	//void SetAnimation(float frameRate, int startingSpriteIndex, int totalSprites, int sourceY = 0);

};

