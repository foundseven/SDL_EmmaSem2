#include "States.h"
#include "Game.h"
#include "GameObject.h"
#include "AnimatedSprite.h"
#include "StateManager.h"
#include"CollisionManager.h"
#include "TextureManager.h"
#include "TiledLevel.h"
#include "EventManager.h"
#include "PlatformingPlayer.h"
#include "Soundmanager.h"


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

	TextureManager::Load("assets/titlescreen1.png", "tSTexture");

	m_titleScreen = TextureManager::GetTexture("tSTexture");
}

void TitleState::Update(float deltaTime)
{

	////////////////////////////////////////////

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


//	std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 254, 254, 34, 255); // Changes the color or the titleState
	SDL_RenderClear(Game::GetInstance().GetRenderer());
	SDL_SetRenderTarget(pRenderer, nullptr); // Set the renderer target to default (screen)
	SDL_RenderCopy(pRenderer, m_titleScreen, nullptr, nullptr);
}

void TitleState::Exit()
{
	std::cout << "Leaving TitleState..." << std::endl;
//	SDL_DestroyTexture(m_titleScreen);
	TextureManager::Unload("tSTexture");


}
// End of TitleState

/////////////////////////////////////////////// Main Menu Screen //////////////////////////////////////////////////////////

// Main Menu Done
void MainMenuScreen::Enter()
{
	std::cout << "Going to Main Menu..." << std::endl;

	TextureManager::Load("assets/mainmenubackground2.png", "mMTexture");
	TextureManager::Load("assets/mm_instruct.png", "instructTexture");
	TextureManager::Load("assets/mm_instruct2.png", "instruct2Texture");

	TextureManager::Load("assets/mm_logo.png", "mMLogoTexture");


	m_mMBack = TextureManager::GetTexture("mMTexture");
	m_mMInstruct = TextureManager::GetTexture("instructTexture");
	m_mMInstruct2 = TextureManager::GetTexture("instruct2Texture");

	m_mMLogo = TextureManager::GetTexture("mMLogoTexture");

	///////////////////////////////////////////////////////////
	//audio
	Soundmanager::LoadMusic("assets/mainmenu.wav", "mainMenuMUS");

}

void MainMenuScreen::Update(float deltaTime)
{

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

	if (!Mix_PlayingMusic())
	{
		Soundmanager::PlayMusic("mainMenuMUS");
	}
	else if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}

void MainMenuScreen::Render()
{
	//	std::cout << "Rendering Main Menu..." << std::endl;
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_RenderClear(pRenderer);
	SDL_SetRenderTarget(pRenderer, nullptr); // Set the renderer target to default (screen)
	
	////////////////////////////////////////////

	SDL_Rect logoPOS{ 307, 100, 600, 200 };// this can change the sizing
	SDL_Rect instructPOS{ 30, 10, 200, 50 };// this can change the sizing
	SDL_Rect instruct2POS{ 1000, 10, 200, 50 };// this can change the sizing

	SDL_RenderCopy(pRenderer, m_mMBack, nullptr, nullptr);
	SDL_RenderCopy(pRenderer, m_mMInstruct, nullptr, &instructPOS);
	SDL_RenderCopy(pRenderer, m_mMInstruct2, nullptr, &instruct2POS);

	SDL_RenderCopy(pRenderer, m_mMLogo, nullptr, &logoPOS); // this can change the sizing

}


void MainMenuScreen::Exit()
{
	std::cout << "Exiting Main Menu" << std::endl;

	TextureManager::Unload("mMTexture");
	TextureManager::Unload("instructTexture");
	TextureManager::Unload("instruct2Texture");
	TextureManager::Unload("mMLogoTexture");

	Soundmanager::UnloadMusic("mainMenuMUS");
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

	TextureManager::Load("assets/background_far.png", "gSBackground");
	TextureManager::Load("assets/mapTiles.png", "tiles");
	TextureManager::Load("assets/player.png", "player");
	
	//m_pLevel = new TiledLevel(24, 40, 32, 32, "assets/Data/Tiledata.txt", "assets/Data/Leveldata.txt", "tiles");
	m_gSBackground = TextureManager::GetTexture("gSBackground");
	
	///////////////////////////////////////////

	m_gSMusic = Mix_LoadMUS("assets/audio/citybackground.mp3");

	Mix_PlayMusic(m_gSMusic, -1);
	 
	/////////////////////////////////////////////

	m_objects.emplace("level", new TiledLevel(24, 40, 32, 32, "assets/Data/Tiledata.txt", "assets/Data/Leveldata.txt", "tiles"));
	m_objects.emplace("player", new PlatformingPlayer({ 0, 448, 64, 64 }, { 288, 480, 64, 64 }));
}

void GameState::Update(float deltaTime)
{
	elapsedTime += deltaTime;

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

	else
	{
		//m_pLevel->Update(deltaTime);
		for (auto object : m_objects)
		{
			object.second->Update(deltaTime);
		}
	}
	
	//checking for collision
	for (unsigned int i = 0; i < static_cast<TiledLevel*>(m_objects["level"])->GetObsticales().size(); i++)
	{
		SDL_FRect* obstaclesColliderTransform = static_cast<TiledLevel*>(m_objects["level"])->GetObsticales()[i]->GetDestinationTransform();
		float obstacleLeft = obstaclesColliderTransform->x;
		float obstacleRight = obstaclesColliderTransform->x + obstaclesColliderTransform->w;
		float obstacleTop = obstaclesColliderTransform->y;
		float obstacleBottom = obstaclesColliderTransform->y + obstaclesColliderTransform->h;

		SDL_FRect* playerColliderTransform = m_objects["player"]->GetDestinationTransform();
		float playerLeft = playerColliderTransform->x;
		float playerRight = playerColliderTransform->x + playerColliderTransform->w;
		float playerTop = playerColliderTransform->y;
		float playerBottom = playerColliderTransform->y + playerColliderTransform->h;

		//check if they collide hori
		bool xOverlap = playerLeft < obstacleRight && playerRight > obstacleLeft;

		//check if the overlap vert
		bool yOverlap = playerTop < obstacleBottom && playerBottom > obstacleTop;

		//to determine which direction the obst came from
		float bottomCollision = obstacleBottom - playerColliderTransform->y;
		float topCollision = playerBottom - obstaclesColliderTransform->y;
		float leftCollision = playerRight - obstaclesColliderTransform->x;
		float rightCollision = obstacleRight - playerColliderTransform->x;

		if (xOverlap && yOverlap)
		{
			PlatformingPlayer* pPlayer = static_cast<PlatformingPlayer*>(m_objects["player"]);

			// Top collision
			if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision)
			{
				pPlayer->StopY();
				pPlayer->SetY(playerColliderTransform->y - topCollision);
				pPlayer->SetGrounded(true);
			}
			//Bottom collision
			if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision)
			{
				pPlayer->StopY();
				pPlayer->SetY(playerColliderTransform->y + bottomCollision);
			}
			// Left collision
			if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision)
			{
				pPlayer->Stop();
				pPlayer->SetY(playerColliderTransform->x - leftCollision);
			}
			// Right collision
			if (rightCollision < leftCollision && rightCollision < topCollision && rightCollision < bottomCollision)
			{
				pPlayer->StopX();
				pPlayer->SetX(playerColliderTransform->x + rightCollision);
			}
		}
	}
}

void GameState::Render()
{
	//std::cout << "Rendering GameState..." << std::endl;
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_SetRenderTarget(pRenderer, nullptr); // Set the renderer target to default (screen)
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); // Set the clear color (black)
	SDL_RenderClear(pRenderer);

	/////////////////////////////////////////////////////////////////


	SDL_RenderCopy(pRenderer, m_gSBackground, nullptr, nullptr);



	for (auto const& i : m_objects)
	{
		i.second->Render();
	}
	
	for (auto object : m_objects)
	{
		object.second->Render();
	}

}

void GameState::Exit()
{
	std::cout << "Exiting GameState..." << std::endl;

	Mix_FreeMusic(m_gSMusic);

	m_gSMusic = nullptr;
	
	for (auto object : m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_objects.clear();

	TextureManager::Unload("gSBackground");
	TextureManager::Unload("tiles");
	TextureManager::Unload("player");

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

	Mix_HaltMusic();

	std::cout << "Entering WinScreen..." << std::endl;
	TextureManager::Load("assets/mainmenubackground2.png", "wSBTexture");
	TextureManager::Load("assets/youwin.png", "winScreenTexture");
	TextureManager::Load("assets/mm_instruct3.png", "wSITexture");
	m_wSBackground = TextureManager::GetTexture("wSBTexture");
	m_wScreen = TextureManager::GetTexture("winScreenTexture");
	m_wSInstruct = TextureManager::GetTexture("wSITexture");

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

	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_RenderClear(pRenderer);
	SDL_SetRenderTarget(pRenderer, nullptr); // Set the renderer target to default (screen)

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 102, 34, 255); // Changes the color or the titleState
	SDL_RenderCopy(pRenderer, m_wSBackground, nullptr, nullptr);

	SDL_Rect winPOS{ 307, 100, 600, 200 };// this can change the sizing
	SDL_RenderCopy(pRenderer, m_wScreen, nullptr, &winPOS);

	SDL_Rect winInstructPOS{ 470, 450, 250, 100 };// this can change the sizing
	SDL_RenderCopy(pRenderer, m_wSInstruct, nullptr, &winInstructPOS);
}

void WinScreen::Exit()
{
	std::cout << "Exiting Win Screen..." << std::endl;
	TextureManager::Unload("wSBTexture");
	TextureManager::Unload("winScreenTexture");
	TextureManager::Unload("wSITexture");


}
// End of Win Screen


/////////////////////////////////////////////// Lose Screen //////////////////////////////////////////////////////////

// Begin of Lose
void LoseScreen::Enter()
{
	Mix_HaltMusic();

	std::cout << "Entering LoseScreen..." << std::endl;
	TextureManager::Load("assets/mainmenubackground2.png", "lSBTexture");
	TextureManager::Load("assets/youlose.png", "loseScreenTexture");
	TextureManager::Load("assets/mm_instruct3.png", "lSITexture");

	m_lSBackground = TextureManager::GetTexture("lSBTexture");
	m_lScreen = TextureManager::GetTexture("loseScreenTexture");
	m_lSInstruct = TextureManager::GetTexture("lSITexture");


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

	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_RenderClear(pRenderer);
	SDL_SetRenderTarget(pRenderer, nullptr); // Set the renderer target to default (screen)

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 230, 0, 0, 255);
	SDL_RenderCopy(pRenderer, m_lSBackground, nullptr, nullptr);
	SDL_Rect losePOS{ 307, 100, 600, 200 };// this can change the sizing
	SDL_RenderCopy(pRenderer, m_lScreen, nullptr, &losePOS);

	SDL_Rect loseInstructPOS{ 470, 450, 250, 100 };// this can change the sizing
	SDL_RenderCopy(pRenderer, m_lSInstruct, nullptr, &loseInstructPOS);

}

void LoseScreen::Exit()
{
	std::cout << "Exiting Lose Screen..." << std::endl;
	TextureManager::Unload("lSBTexture");
	TextureManager::Unload("loseScreenTexture");
	TextureManager::Unload("lSITexture");


}
// End of Lose Screen

/////////////////////////////////////////////// Credits //////////////////////////////////////////////////////////

// Credits Finished
void CreditScreen::Enter()
{
	std::cout << "Credit Screen activated!" << std::endl;

	Mix_ResumeMusic();

	//back
	TextureManager::Load("assets/credit1.png", "creditBTexture");
	m_cSBackground1 = TextureManager::GetTexture("creditBTexture");

	//mid
	TextureManager::Load("assets/credit2.png", "creditB2Texture");
	m_cSBackground2 = TextureManager::GetTexture("creditB2Texture");

	//mid 2
	TextureManager::Load("assets/credit3.png", "creditB3Texture");
	m_cSBackground3 = TextureManager::GetTexture("creditB3Texture");

	//name credit
	TextureManager::Load("assets/mynamecred.png", "creditNameTexture");
	m_nCredit = TextureManager::GetTexture("creditNameTexture");

	//instruct
	TextureManager::Load("assets/mm_instruct4.png", "cSITexture");
	m_sICredit = TextureManager::GetTexture("cSITexture");

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
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_RenderClear(pRenderer);
	SDL_SetRenderTarget(pRenderer, nullptr); // Set the renderer target to default (screen)


	SDL_RenderCopy(pRenderer, m_cSBackground1, nullptr, nullptr);
	SDL_RenderCopy(pRenderer, m_cSBackground2, nullptr, nullptr);
	SDL_RenderCopy(pRenderer, m_cSBackground3, nullptr, nullptr);

	SDL_Rect nameCreditPOS{ 400, 450, 400, 100 };// this can change the sizing
	SDL_RenderCopy(pRenderer, m_nCredit, nullptr, &nameCreditPOS);

	SDL_Rect cSIPOS{ 20, 50, 200, 50 };// this can change the sizing
	SDL_RenderCopy(pRenderer, m_sICredit, nullptr, &cSIPOS);

}

void CreditScreen::Exit()
{
	std::cout << "Leaving the Main Menu..." << std::endl;

	Mix_PauseMusic();

	TextureManager::Unload("creditBTexture");
	TextureManager::Unload("creditB2Texture");
	TextureManager::Unload("creditB3Texture");

	TextureManager::Unload("creditNameTexture");
	TextureManager::Unload("cSITexture");


}
// End of Credits