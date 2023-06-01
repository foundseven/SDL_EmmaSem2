#pragma once
#include <SDL.h>

class Game
{
public:
	static const int kWidth = 1024; //screen width
	static const int kHeight = 768; //sccreen height
	static const int kRectangleSpeed = 300;

public:
	static Game& GetInstance();
	bool init(const char* title, int xPos, int yPos);
	bool IsRunning();
	void HandleEvents();
	void Quit();
	void Update(float deltaTime);
	void Render();
	void Clear();

	SDL_Window* GetWindow() { return m_pWindow; }
	SDL_Renderer* GetRenderer() { return m_pRenderer; }

private:
	Game(); // private constructor

	bool m_running;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	SDL_FRect m_RectangleTransform;
	const Uint8* m_keyStates;
};