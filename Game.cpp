#include "Game.h"
#include "StateManager.h"
#include "States.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Soundmanager.h"
#include <iostream>

//to refer to last semester this is all the stuff that was in that main section. this is the creaton of our window, init the engine

Game::Game()
	: m_running(false)
	, m_pWindow(nullptr)
	, m_pRenderer(nullptr)
	, m_keyStates(nullptr)
{

}

Game& Game::GetInstance()
{
	static Game* pInstance = new Game();
	return *pInstance;
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
	{
		std::cout << "Mix_OpenAudio() failed. Error: " << SDL_GetError() << std::endl;
	}

	if (Soundmanager::Init())
	{
		std::cout << "Soundmanager Init() succeeded. Error: " << std::endl;
	}
	else
	{
		std::cout << "Soundmanager Init() failed. Error: " << std::endl;
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		return -1;

	}
	std::cout << "Initialization Successful!" << std::endl;

	EventManager::Init();

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
	EventManager::HandleEvents();
}

void Game::Quit()
{
	m_running = false;
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

}

//clearing the engine
void Game::Clear()
{
	std::cout << "Clearing engine..." << std::endl;
	StateManager::Quit();
	TextureManager::Quit();
	EventManager::Quit();
	Soundmanager::Quit();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}