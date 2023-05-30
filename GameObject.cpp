#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(float x, float y, float w, float h,
						Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	: m_Transform{x, y, w, h}
	, m_Color {r, g, b, a}
{

}
void GameObject::Draw(SDL_Renderer* pRenderer)
{

	SDL_SetRenderDrawColor(pRenderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	SDL_RenderFillRectF(pRenderer, &m_Transform);

}

void  GameObject::UpdatePositionX(float x)
{
	m_Transform.x += x;
}
void GameObject::UpdatePositionY(float y)
{
	m_Transform.y += y;
}

