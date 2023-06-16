#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>
#include <map>
#include <string>

#include "GameObject.h"
#include "AnimatedSprite.h"


class GameObject;
class AnimatedSpriteObject;
class TiledLevel;


class State // This is the abstract base class for all states
{
public:
	State() = default;
	virtual ~State() = default; // Modern alternative to {}

	virtual void Enter() = 0; // 0 means pure virtual - must be defined in subclass
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual void Resume() {}

	std::map<std::string, GameObject* > m_objects;
};

////////////////////////////////

class TitleState : public State
{

private:
	Uint32 startTime;

public:

	float elapsedTime;
	SDL_Texture* m_titleScreen;

	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;


};

////////////////////////////////

class MainMenuScreen : public State
{

private:

public:

	Mix_Music* m_pMenuMusic;

	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;

	//GameObject* m_Player;
	SDL_Texture* m_mMBack;
	SDL_Texture* m_mMInstruct;
	SDL_Texture* m_mMInstruct2;
	//SpriteObject* m_mMInstruct;
	SDL_Texture* m_mMLogo;




};

////////////////////////////////

class GameState : public State
{
public:

	Mix_Music* m_gSMusic;
	Mix_Chunk* m_WalkSoundEffect;


	static const int kPlayerSpeed = 400;
	std::vector<AnimatedSpriteObject*> m_GameObjects;
	//TiledLevel* m_pLevel;

	GameObject* m_Player;

	SDL_Texture* m_pPlayerTexture;
	SDL_Texture* m_pObjectTexture;

	SDL_Texture* m_gSBackground;
	SDL_Texture* m_gSPlayer;
	SDL_Texture* m_gSEnemy;



	Mix_Music* m_pMusic;

	float elapsedTime;

	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;


private:
	Uint32 startTime;

};

////////////////////////////////

class PauseState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

////////////////////////////////

class CreditScreen : public State
{

private:

public:

	SDL_Texture* m_cSBackground1;
	SDL_Texture* m_cSBackground2;
	SDL_Texture* m_cSBackground3;

	SDL_Texture* m_nCredit;
	SDL_Texture* m_sICredit;

	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;


};

////////////////////////////////

class WinScreen : public State
{
public:

	SDL_Texture* m_wScreen;
	SDL_Texture* m_wSBackground;
	SDL_Texture* m_wSInstruct;

	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

////////////////////////////////

class LoseScreen : public State
{
public:

	SDL_Texture* m_lScreen;
	SDL_Texture* m_lSBackground;
	SDL_Texture* m_lSInstruct;


	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};