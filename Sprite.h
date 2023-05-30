#pragma once
#include <SDL.h>

class Sprite
{
protected:
	SDL_Rect m_sourceTransform; //source pixel from image
	SDL_FRect m_destinationTransform; //destination window
	int m_angle; //angle of sprite

public:
	Sprite();
	Sprite(SDL_Rect sourceTransform, SDL_FRect destinationTransform, int angle);
	SDL_Rect& GetSourceTransform() { return m_sourceTransform;  }
	SDL_FRect& GetDestinationTransform() { return m_destinationTransform; }
	int GetAngle() { return m_angle; }
};

