#include "Game.h"
#include "StateManager.h"
#include "States.h"
#include <iostream>

//to refer to last semester this is all the stuff that was in that main section. this is the creaton of our window, init the engine

Game::Game()
	: m_running(false)
	, m_pWindow(nullptr)
	, m_pRenderer(nullptr)
	, m_RectangleTransform{ kWidth / 2,kHeight / 2, 100, 100 }
	, m_keyStates(nullptr)
{

}

Game& Game::GetInstance()
{
	static Game* instance = new Game();
	return *instance;
}

bool Game::init(const char* title, int xPos, int yPos)
{
	std::cout << "Initializing engine..." << std::endl;
	// Call to SDL_Init(). This will initialize SL and the video subsystem.
	int errorCode = SDL_Init(SDL_INIT_EVERYTHING);
	if (errorCode == 0)
	{
		std::cout << "SDL_Init() succeeded." << std::endl;
	}
	else
	{
		std::cout << "SDL_Init() failed. Error code " << errorCode << ": " << SDL_GetError() << std::endl;
		system("pause");
		return errorCode;
	}

	// Attempt to create a maximized window that can be restored to a KWidth x kHeight, centered window.
	m_pWindow = SDL_CreateWindow("GAME 1017",             // title
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,   // x , y
		kWidth, kHeight,                                  // witdh, height
		0);                                               // flags

	if (m_pWindow != nullptr)
	{
		std::cout << "SDL_CreateWindow() succeeded." << std::endl;
	}
	else
	{
		std::cout << "SDL_CreateWindow() failed. Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	// Attempts to creat a hardware-accelerated renderer for our window.
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_pRenderer != nullptr)
	{
		std::cout << "SDL_CreateRenderer() succeeded." << std::endl;
	}
	else
	{
		std::cout << "SDL_CreateRenderer() failed. Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return -1;
	}

	std::cout << "Initialization Successful!" << std::endl;

	StateManager::PushState(new TitleState());

	m_keyStates = SDL_GetKeyboardState(nullptr);

	m_running = true;
	return 0;
}

//making sure the game is running
bool Game::IsRunning()
{
	return m_running;
}

//if anything is happening on the screen, just make sure the game is still running
void Game::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		}
	}
}

//this is for our input
bool Game::KeyDown(SDL_Scancode key)
{
	if (m_keyStates)
	{
		return m_keyStates[key] == 1;
	}
	return false;
}

//this is our void input stuff
void Game::Update(float deltaTime)
{
	StateManager::Update(deltaTime);
}

//this is just drawing it all to the screen
void Game::Render()
{
	StateManager::Render();
	SDL_RenderPresent(m_pRenderer); // Flip buffers - send data to window.

	SDL_SetRenderDrawColor(m_pRenderer, 0, 128, 255, 255);
	SDL_RenderClear(m_pRenderer);

	// Any drawing here...

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
	SDL_RenderFillRectF(m_pRenderer, &m_RectangleTransform);

}

//clearing the engine
void Game::Clear()
{
	std::cout << "Clearing engine..." << std::endl;
	StateManager::Quit();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}