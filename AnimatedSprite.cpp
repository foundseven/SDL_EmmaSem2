#include "AnimatedSprite.h"

//all green in new code

AnimatedSpriteObject::AnimatedSpriteObject(const SDL_Rect source, const SDL_FRect destination)
	: SpriteObject(source, destination)
	, m_currentSpriteIndex(0)
	, m_totalSprite(0)
	, m_currentTime(0)
	, m_frameRate(0)
	, m_startingSpriteIndex(0)
{

}

void AnimatedSpriteObject::SetAnimation(float frameRate, int startingSpriteIndex, int totalSprites, int sourceY)
{
	m_currentTime = 0;
	m_frameRate = frameRate;
	m_currentSpriteIndex = 0;
	m_startingSpriteIndex = startingSpriteIndex;
	m_totalSprite = totalSprites;
	m_sourceTransform.x = m_sourceTransform.w * startingSpriteIndex;
	m_sourceTransform.y = sourceY;
}


void AnimatedSpriteObject::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime > m_frameRate)
	{
		m_currentTime = m_frameRate - m_currentTime;
		m_currentSpriteIndex++;
		if (m_currentSpriteIndex == m_maxSprites)
		{
			m_currentSpriteIndex = 0;
		}
	}
	m_sourceTransform.x = m_sourceTransform.w * (m_startingSpriteIndex * m_currentSpriteIndex);
	//m_sourceTransform.x = m_sourceTransform.w * m_currentSpriteIndex;

}
