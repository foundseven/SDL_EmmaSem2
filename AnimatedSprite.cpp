#include "AnimatedSprite.h"
AnimatedSprite::AnimatedSprite(int angle, float frameRate, int maxSprite,
	SDL_Rect sourceTransform, SDL_FRect destinationTransform)
	: Sprite(sourceTransform, destinationTransform, angle)
	, m_currentSpriteIndex {0}
	, m_maxSprite {maxSprite}
	, m_currentTime {0}
	, m_frameRate {frameRate}
{

}
void AnimatedSprite::Animate(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime > m_frameRate)
	{
		m_currentTime = m_frameRate - m_currentTime;
		m_currentSpriteIndex++;
		if (m_currentSpriteIndex == m_maxSprite)
		{
			m_currentSpriteIndex = 0;
		}
	}

	m_sourceTransform.x = m_sourceTransform.w * m_currentSpriteIndex; //this line updates the x pos to go over to the next one
}