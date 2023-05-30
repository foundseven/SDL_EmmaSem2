#pragma once
#include <SDL.h>

class Sprite
{
protected:
	SDL_Rect m_sourceTransform;
	SDL_FRect m_destinationTransform;
	int m_angle;

public:
	Sprite();
	Sprite(SDL_Rect sourceTransform, SDL_FRect destinationTransform, int angle);
	SDL_Rect& GetSourceTransform() { return m_sourceTransform;  }
	SDL_FRect& GetDestinationTransform() { return m_destinationTransform; }
	int GetAngle() { return m_angle; }
};

