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

	////////////////////////////////////

	GameObject()
		: m_destinationTransform({ 0, 0, 0, 0 })
	{}

	GameObject(const SDL_FRect destination)
		: m_destinationTransform({ destination })
	{}

	virtual ~GameObject() = default;

	virtual void Update(float deltaTime)
	{
	};
	virtual void Render()
	{
	};
	SDL_FRect* GetDestinationTransform() { return &m_destinationTransform; }

private:
	SDL_FRect m_Transform;
	SDL_Color m_Color;

protected:
	SDL_FRect m_destinationTransform;

};

