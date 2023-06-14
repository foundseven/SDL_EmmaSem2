#pragma once
#include <SDL.h>

#include "GameObject.h"

class SpriteObject : public GameObject
{
public:
	SpriteObject();
	//SpriteObject(SDL_Rect sourceTransformation, SDL_FRect destinationTransform, int angle);

	SpriteObject(const SDL_Rect source, const SDL_FRect destination)
		: GameObject(destination)
		, m_sourceTransform(source)
	{ }
	const SDL_Rect* GetSourceTransform() const { return &m_sourceTransform; }

	//???
	const SDL_FRect* GetDestinationTransform() const { return &m_destinationTransform; }
	int GetAngle() { return m_angle; }

	void Render() override {}
	void Update(float deltaTime) override {}

protected:

	SDL_Rect m_sourceTransform;
	SDL_FRect m_destinationTransform;
	int m_angle;
};
