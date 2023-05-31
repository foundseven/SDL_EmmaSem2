#include "States.h"
#include "Game.h"
#include "GameObject.h"
#include "AnimatedSprite.h"
#include "StateManager.h"
#include"CollisionManager.h"
#include "TextureManager.h"
#include "TiledLevel.h"
#include "EventManager.h"

#include <iostream>
#include <Windows.h>
#include <SDL_image.h>
#include <SDL_mixer.h>




/////////////////////////////////////////////// TITLESTATE //////////////////////////////////////////////////////////

// Title Finished
void TitleState::Enter()
{
	std::cout << "TitleState activated!" << std::endl;
	elapsedTime = 0.0f;
}

void TitleState::Update(float deltaTime)
{
	m_titleScreen = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/titlescreen1.png");
	if (!m_titleScreen)
	{
		std::cout << "Failed to load background texture: " << IMG_GetError() << std::endl;
	}

	elapsedTime += deltaTime;

	if (elapsedTime >= 4.0f)
	{
		std::cout << "Moving to GameState" << std::endl;
		StateManager::ChangeState(new MainMenuScreen()); // Change to the menu after 4 seconds
	}
}

void TitleState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();


	//std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 254, 254, 34, 255); // Changes the color or the titleState
	SDL_RenderClear(Game::GetInstance().GetRenderer());
	SDL_SetRenderTarget(pRenderer, nullptr); // Set the renderer target to default (screen)

	SDL_RenderCopy(pRenderer, m_titleScreen, nullptr, nullptr);
}

void TitleState::Exit()
{
	std::cout << "Leaving TitleState..." << std::endl;
	SDL_DestroyTexture(m_titleScreen);

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
	TextureManager::Load("assets/enemy_idle.png", "enemyTexture");

	m_mMBack = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/mainmenubackground.png");
	if (!m_mMBack)
	{
		std::cout << "Failed to load background texture: " << IMG_GetError() << std::endl;

	}

	TextureManager::Load("assets/mm_instruct.png", "instructTexture");
	TextureManager::Load("assets/mm_logo.png", "mMLogoTexture");
	SDL_Rect rect;
	SDL_FRect frect;

	SDL_QueryTexture(TextureManager::GetTexture("instructTexture"), NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;

	frect.x = 0;
	frect.y = 0;
	frect.w = rect.w;
	frect.h = rect.h;
	//m_mMInstruct = new GameObject(rect, frect);


	Game& GameInstance = Game::GetInstance();
	////////////////////////////////////////////

	if (EventManager::KeyPressed(SDL_SCANCODE_G))
	{
		std::cout << "Changing to GameState" << std::endl;
		StateManager::ChangeState(new GameState()); // Change to GS
	}

	if (EventManager::KeyPressed(SDL_SCANCODE_C))
	{
		std::cout << "Rolling credits!" << std::endl;
		StateManager::ChangeState(new CreditScreen()); // Change to Credits
	}
}

void MainMenuScreen::Render()
{
	//	std::cout << "Rendering Main Menu..." << std::endl;
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	//for background
	SDL_SetRenderTarget(pRenderer, nullptr); // Set the renderer target to default (screen)
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); // Set the clear color (black)
	SDL_RenderClear(pRenderer);
	SDL_RenderCopy(pRenderer, m_mMBack, nullptr, nullptr);
	SDL_RenderCopy(pRenderer, m_mMInstruct, nullptr, nullptr);
	SDL_RenderCopy(pRenderer, m_mMLogo, nullptr, nullptr);

	//SDL_Rect playerIntRect = MathManager::ConvertFRect2Rect(m_Player->GetTransform());
	//SDL_RenderCopy(pRenderer, TextureManager::GetTexture("instructTexture"), nullptr, &playerIntRect);

}


void MainMenuScreen::Exit()
{
	std::cout << "Exiting Main Menu" << std::endl;

	SDL_DestroyTexture(m_mMBack);
	SDL_DestroyTexture(m_mMBack);
	SDL_DestroyTexture(m_mMLogo);

}
// End of TitleState


/////////////////////////////////////////////// GAMESTATE ////////////////////////////////////////////////////////////

// Begin of GameState
void GameState::Enter() // Used for initialization
{
	//startTime = SDL_GetTicks();
	std::cout << "Entering GameState..." << std::endl;

	elapsedTime = 0.0f;

	SDL_Rect sourceTransform{ 0, 0, 64, 64 };
	/*m_GameObjects.push_back(new AnimatedSprite(0, 0.1, 4, sourceTransform,{ 100, 500, 64, 64 }));
	m_GameObjects.push_back(new AnimatedSprite(0, 0.1, 4, sourceTransform, { 400, 500, 64, 64 }));
	m_GameObjects.push_back(new AnimatedSprite(0, 0.1, 4, sourceTransform, { 700, 500, 64, 64 }));*/


	//m_Player = new GameObject(Game::kWidth / 2, Game::kHeight / 2, 27, 36, 255, 255, 255, 255); //this is for the player as of right now... width and height


	m_backgroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/background_far.png");
	if (!m_backgroundTexture)
	{
		std::cout << "Failed to load background texture: " << IMG_GetError() << std::endl;

	}
	TextureManager::Load("assets/punk.png", "playerTexture");
	TextureManager::Load("assets/enemy_idle.png", "enemyTexture");
	SDL_Rect rect;
	SDL_FRect frect;

	//SDL_QueryTexture(TextureManager::GetTexture());

	m_pMusic = Mix_LoadMUS("assets/citybackground.mp3");

	Mix_PlayMusic(m_pMusic, -1);

}

void GameState::Update(float deltaTime)
{
	elapsedTime += deltaTime;

	Game& GameInstance = Game::GetInstance();

	if (EventManager::KeyPressed(SDL_SCANCODE_M))
	{
		std::cout << "Going back to the Main Menu" << std::endl;
		StateManager::ChangeState(new TitleState()); // Change to new TitleState
	}
	if (EventManager::KeyPressed(SDL_SCANCODE_P))
	{
		std::cout << "Changing to PauseState" << std::endl;
		StateManager::PushState(new PauseState()); // Change to new PauseState
	}
	if (elapsedTime >= 30.0f)
	{
		std::cout << "You Win!" << std::endl;
		StateManager::PushState(new WinScreen());
	}
	//else
	//{
	//	if (EventManager::KeyPressed(SDL_SCANCODE_W))
	//		m_Player->UpdatePositionY(-kPlayerSpeed * deltaTime);

	//	if (EventManager::KeyPressed(SDL_SCANCODE_S))
	//		m_Player->UpdatePositionY(kPlayerSpeed * deltaTime);

	//	if (EventManager::KeyPressed(SDL_SCANCODE_A))
	//		m_Player->UpdatePositionX(-kPlayerSpeed * deltaTime);

	//	if (EventManager::KeyPressed(SDL_SCANCODE_D))
	//		m_Player->UpdatePositionX(kPlayerSpeed * deltaTime);
	//}
	//	//updating the animation
	//	for (AnimatedSprite* pObject : m_GameObjects)
	//	{
	//		pObject->Animate(deltaTime);
	//	}

	//	//check for collision
	//	for (AnimatedSprite* pObject : m_GameObjects)
	//	{
	//		if (CollisionManager::AABBCheck(m_Player->GetTransform(), pObject->GetDestinationTransform()))
	//		{
	//			std::cout << "L! You LOSE!" << std::endl;
	//			StateManager::PushState(new LoseScreen()); // Change to new LoseState
	//		}

	//	}		
}

void GameState::Render()
{
	//std::cout << "Rendering GameState..." << std::endl;
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	//SDL_SetRenderDrawColor(pRenderer, &m_backgroundTexture ); // Changes the color or the GameState
	SDL_SetRenderTarget(pRenderer, nullptr); // Set the renderer target to default (screen)
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); // Set the clear color (black)
	SDL_RenderClear(pRenderer);
	SDL_RenderCopy(pRenderer, m_backgroundTexture, nullptr, nullptr);

	//for (AnimatedSprite* pObject : m_GameObjects)
	//{
	//	{
	//		//pObject->Draw(pRenderer);
	//		SDL_FPoint pivot = { 0, 0 };
	//		SDL_RenderCopyExF(pRenderer, TextureManager::GetTexture("enemyTexture"), &(pObject->GetSourceTransform())
	//			, &(pObject->GetDestinationTransform())
	//			, (pObject->GetAngle()), &pivot, SDL_FLIP_NONE);
	//	}
	//}

	//SDL_Rect playerIntRect = MathManager::ConvertFRect2Rect(m_Player->GetTransform());
	//SDL_RenderCopy(pRenderer, TextureManager::GetTexture("playerTexture"), nullptr, &playerIntRect);

	SDL_RenderPresent(pRenderer);
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

	SDL_DestroyTexture(m_backgroundTexture);
	SDL_DestroyTexture(m_pPlayerTexture);
	SDL_DestroyTexture(m_pObjectTexture);

	Mix_FreeMusic(m_pMusic);
	m_pMusic = nullptr;
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
	if (EventManager::KeyPressed(SDL_SCANCODE_ESCAPE))
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
	if (EventManager::KeyPressed(SDL_SCANCODE_SPACE))
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
	if (EventManager::KeyPressed(SDL_SCANCODE_SPACE))
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
	if (EventManager::KeyPressed(SDL_SCANCODE_ESCAPE))
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