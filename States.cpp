#include "States.h"
#include "Game.h"
#include "GameObject.h"
#include "AnimatedSprite.h"
#include "StateManager.h"
#include"CollisionManager.h"
#include <Windows.h>
#include <SDL_image.h>



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
	//std::cout << "Rendering TitleState..." << std::endl;
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
//	std::cout << "Rendering Main Menu..." << std::endl;
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
	startTime = SDL_GetTicks();
	std::cout << "Entering GameState..." << std::endl;

	//m_GameObjects.push_back(new GameObject(100, 100, 30, 30));
	//m_GameObjects.push_back(new GameObject(400, 400, 30, 30));
	//m_GameObjects.push_back(new GameObject(700, 100, 30, 30));

	SDL_Rect sourceTransform{ 0, 0, 64, 64 };
	m_GameObjects.push_back(new AnimatedSprite(0, 0.1, 4, sourceTransform,{ 100, 100, 64, 64 }));
	m_GameObjects.push_back(new AnimatedSprite(0, 0.1, 4, sourceTransform, { 400, 400, 64, 64 }));
	m_GameObjects.push_back(new AnimatedSprite(0, 0.1, 4, sourceTransform, { 700, 100, 64, 64 }));


	m_Player = new GameObject(Game::kWidth / 2, Game::kHeight / 2, 192, 48, 200, 200, 200, 255);

	m_pPlayerTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/Punk_idle.png");

	m_pObjectTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/enemy_idle.png");

}

void GameState::Update([[maybe_unused]]float deltaTime)
{
	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_M))
	{
		std::cout << "Going back to the Main Menu" << std::endl;
		StateManager::ChangeState(new TitleState()); // Change to new TitleState
	}
	else if (GameInstance.KeyDown(SDL_SCANCODE_P))
	{
		std::cout << "Changing to PauseState" << std::endl;
		StateManager::PushState(new PauseState()); // Change to new PauseState
	}
	else
	{
		if (GameInstance.KeyDown(SDL_SCANCODE_W))
		{
			m_RectangleTransform.y -= kRectangleSpeed * deltaTime;
		}
		if (GameInstance.KeyDown(SDL_SCANCODE_S))
		{
			m_RectangleTransform.y += kRectangleSpeed * deltaTime;
		}
		if (GameInstance.KeyDown(SDL_SCANCODE_A))
		{
			m_RectangleTransform.x -= kRectangleSpeed * deltaTime;
		}
		if (GameInstance.KeyDown(SDL_SCANCODE_D))
		{
			m_RectangleTransform.x += kRectangleSpeed * deltaTime;
		}

		//updating the animation
		for (AnimatedSprite* pObject : m_GameObjects)
		{
			pObject->Animate(deltaTime);
		}

		//check for collision

		for (std::vector<AnimatedSprite*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); )
		{

			AnimatedSprite* pObject = (*it);
			
			//if (pObject != m_Player)
				
			if (CollisionManager::AABBCheck(m_Player->GetTransform(), pObject->GetDestinationTransform()))
			{
				std::cout << "Player hit!!" << std::endl;
				it = m_GameObjects.erase(it);
				delete pObject;
				pObject = nullptr;
				StateManager::PushState(new LoseScreen()); //pushing to a new one rather than making it totally new 
			}
			
			else
			{
				Uint32 elapsedTime = SDL_GetTicks() - startTime;

				if (elapsedTime >= 20000)
				{
					std::cout << "You Win!" << std::endl;
					it++;
					StateManager::PushState(new WinScreen());
				}
			}
		}
			
	}
}

void GameState::Render()
{
	std::cout << "Rendering GameState..." << std::endl;
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255); // Changes the color or the GameState
	SDL_RenderClear(pRenderer);

	for (AnimatedSprite* pObject : m_GameObjects)
	{
		
		{
			//pObject->Draw(pRenderer);
			SDL_FPoint pivot = { 0, 0 };
			SDL_RenderCopyExF(pRenderer, m_pObjectTexture, &(pObject->GetSourceTransform())
				, &(pObject->GetDestinationTransform())
				, (pObject->GetAngle()), &pivot, SDL_FLIP_NONE);
		}
	}

	SDL_Rect playerIntRect = MathManager::ConvertFRect2Rect(m_Player->GetTransform());
	SDL_RenderCopy(pRenderer, m_pPlayerTexture, nullptr, &playerIntRect);
}

void GameState::Exit()
{
	std::cout << "Exiting GameState..." << std::endl;

	for (AnimatedSprite* pObject : m_GameObjects)
	{

		delete pObject;
		pObject = nullptr;
	}

	delete m_Player;
	m_Player = nullptr;

	SDL_DestroyTexture(m_pPlayerTexture);
	SDL_DestroyTexture(m_pObjectTexture);
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
	//std::cout << "Rendering PauseState..." << std::endl;
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
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_SPACE))
	{
		std::cout << "Changing to Main Menu" << std::endl;
		StateManager::ChangeState(new MainMenuScreen()); // Change to MM
	}
}

void WinScreen::Render()
{
	//std::cout << "Rendering Win Screen..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 102, 34, 255); // Changes the color or the titleState
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void WinScreen::Exit()
{
	std::cout << "Exiting Win Screen..." << std::endl;
}
// End of Win Screen


/////////////////////////////////////////////// Lose Screen //////////////////////////////////////////////////////////

// Begin of Lose
void LoseScreen::Enter()
{
	std::cout << "Entering LoseScreen..." << std::endl;
}

void LoseScreen::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_SPACE))
	{
		std::cout << "Changing to Main Menu" << std::endl;
		StateManager::ChangeState(new MainMenuScreen()); // Change to MM
	}
}

void LoseScreen::Render()
{
	//std::cout << "Rendering LoseScreen..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 230, 0, 0, 255); 
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void LoseScreen::Exit()
{
	std::cout << "Exiting Lose Screen..." << std::endl;
}
// End of Lose Screen

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
	//std::cout << "Rolling Credits!" << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 207, 241, 255); // Changes the color or the titleState
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void CreditScreen::Exit()
{
	std::cout << "Leaving the Main Menu..." << std::endl;
}
// End of Credits