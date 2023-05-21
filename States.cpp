#include "States.h"
#include "Game.h"
#include "StateManager.h"
#include <iostream>


/////////////////////////////////////////////// TITLESTATE //////////////////////////////////////////////////////////

// Title Finished
void TitleState::Enter()
{
	std::cout << "TitleState activated!" << std::endl;
	startTime = SDL_GetTicks();
}

void TitleState::Update(float deltaTime)
{
	Uint32 elapsedTime = SDL_GetTicks() - startTime;

	if (elapsedTime >= 4000) 
	{
		std::cout << "Moving to GameState" << std::endl;
		StateManager::ChangeState(new MainMenuScreen()); // Change to the menu after 4 seconds
	}
}

void TitleState::Render()
{
	std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 254, 254, 34, 255); // Changes the color or the titleState
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void TitleState::Exit()
{
	std::cout << "Leaving TitleState..." << std::endl;
}
// End of TitleState

/////////////////////////////////////////////// Main Menu Screen //////////////////////////////////////////////////////////

// Main Menu Done
void MainMenuScreen::Enter()
{
	std::cout << "Going to Main Menu..." << std::endl;
	
}

void MainMenuScreen::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_G))
	{
		std::cout << "Changing to GameState" << std::endl;
		StateManager::ChangeState(new GameState()); // Change to GS
	}

	if (Game::GetInstance().KeyDown(SDL_SCANCODE_C))
	{
		std::cout << "Rolling credits!" << std::endl;
		StateManager::ChangeState(new CreditScreen()); // Change to Credits
	}
}

void MainMenuScreen::Render()
{
	std::cout << "Rendering Main Menu..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 148, 0, 211, 255); // Changes the color or the titleState
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void MainMenuScreen::Exit()
{
	std::cout << "Exiting Main Menu" << std::endl;
}
// End of TitleState


/////////////////////////////////////////////// GAMESTATE ////////////////////////////////////////////////////////////

// Begin of GameState
void GameState::Enter() // Used for initialization
{
	std::cout << "Entering GameState..." << std::endl;

	m_RectangleTransform.x = Game::kWidth / 2;
	m_RectangleTransform.y = Game::kHeight / 2;
	m_RectangleTransform.w = 60;
	m_RectangleTransform.h = 100;
}

void GameState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_M))
	{
		std::cout << "Going back to the Main Menu" << std::endl;
		StateManager::ChangeState(new TitleState()); // Change to new TitleState
	}
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_P))
	{
		std::cout << "Changing to PauseState" << std::endl;
		StateManager::PushState(new PauseState()); // Change to new PauseState
	}
	else
	{
		if (Game::GetInstance().KeyDown(SDL_SCANCODE_W))
			m_RectangleTransform.y -= kRectangleSpeed * deltaTime;
		if (Game::GetInstance().KeyDown(SDL_SCANCODE_S))
			m_RectangleTransform.y += kRectangleSpeed * deltaTime;
		if (Game::GetInstance().KeyDown(SDL_SCANCODE_A))
			m_RectangleTransform.x -= kRectangleSpeed * deltaTime;
		if (Game::GetInstance().KeyDown(SDL_SCANCODE_D))
			m_RectangleTransform.x += kRectangleSpeed * deltaTime;
	}
}

void GameState::Render()
{
	std::cout << "Rendering GameState..." << std::endl;
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 0, 255, 255); // Changes the color or the GameState
	SDL_RenderClear(pRenderer);

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderFillRectF(pRenderer, &m_RectangleTransform);
}

void GameState::Exit()
{
	std::cout << "Exiting GameState..." << std::endl;
}

void GameState::Resume()
{
	std::cout << "Resuming GameState..." << std::endl;
}
// End of Gamestate

/////////////////////////////////////////////// PAUSESTATE ///////////////////////////////////////////////////////////

// Pause State is Finished
void PauseState::Enter()
{
	std::cout << "Entering PauseState..." << std::endl;
}

void PauseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_ESCAPE))
	{
		std::cout << "Moving back to the Game State..." << std::endl;
		StateManager::PopState(); // Change to new PauseState
	}
	
}

void PauseState::Render()
{
	std::cout << "Rendering PauseState..." << std::endl;
	// First render of the GameState
	StateManager::GetStates().front()->Render();

	// Now render rest of PauseState
	SDL_SetRenderDrawBlendMode(Game::GetInstance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 128, 128, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &rect);
}

void PauseState::Exit()
{
	std::cout << "Exiting PauseState..." << std::endl;
}
// End of PauseState

/////////////////////////////////////////////// Win Screen //////////////////////////////////////////////////////////

// Begin of TitleState
void WinScreen::Enter()
{
	std::cout << "Entering WinScreen..." << std::endl;
}

void WinScreen::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_N))
	{
		std::cout << "Changing to Win Screen" << std::endl;
		StateManager::ChangeState(new GameState()); // Change to new GameState
	}
}

void WinScreen::Render()
{
	std::cout << "Rendering Win Screen..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 50, 205, 50, 255); // Changes the color or the titleState
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void WinScreen::Exit()
{
	std::cout << "Exiting Win Screen..." << std::endl;
}
// End of TitleState

/////////////////////////////////////////////// Credits //////////////////////////////////////////////////////////

// Credits Finished
void CreditScreen::Enter()
{
	std::cout << "Credit Screen activated!" << std::endl;
}

void CreditScreen::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_ESCAPE))
	{
		std::cout << "Moving back to Main Menu..." << std::endl;
		StateManager::ChangeState(new MainMenuScreen()); // Change back to main menu
	}
}

void CreditScreen::Render()
{
	std::cout << "Rolling Credits!" << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 207, 241, 255); // Changes the color or the titleState
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void CreditScreen::Exit()
{
	std::cout << "Leaving the Main Menu..." << std::endl;
}
// End of Credits