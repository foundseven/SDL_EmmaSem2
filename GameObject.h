#pragma once


#include <SDL.h>


class GameObject
{
public:
	GameObject(float x, float y, float w, float h,
		Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void Draw(SDL_Renderer* pRenderer);
	void UpdatePositionX(float x);
	void UpdatePositionY(float y);
	SDL_FRect& GetTransform() { return m_Transform; }

private:
	SDL_FRect m_Transform;
	SDL_Color m_Color;


public:
	GameObject()
		: m_destinationTransform({ 0, 0, 0, 0 })
	{}

	GameObject(const SDL_FRect destination)
		: m_destinationTransform({ destination })
	{}

	virtual ~GameObject() = default;

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	SDL_FRect* GetDestinationTransform() { return &m_destinationTransform; }


protected:
	SDL_FRect m_destinationTransform;
};

