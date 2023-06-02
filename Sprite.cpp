#include "Sprite.h"

SpriteObject::SpriteObject()
	: m_sourceTransform{ 0, 0, 0, 0 }
	, m_destinationTransform{ 0,0,0,0 }
	, m_angle(0)
{

}

SpriteObject::SpriteObject(SDL_Rect source, SDL_FRect destination, int angle = 0)
	: m_sourceTransform{ source }
	, m_destinationTransform{ destination }
	, m_angle(angle)
{

}