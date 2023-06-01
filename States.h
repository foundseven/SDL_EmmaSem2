#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>
#include "GameObject.h"
#include "AnimatedSprite.h"


class GameObject;
class AnimatedSprite;
class TiledLevel;


class State // This is the abstract base class for all states
{
public:
	//State() = default;
	//virtual ~State() = default; // Modern alternative to {}

	virtual void Enter() = 0; // 0 means pure virtual - must be defined in subclass
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual void Resume() {}
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
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;

	GameObject* m_Player;
	SDL_Texture* m_mMBack;
	SDL_Texture* m_mMInstruct;
	//SpriteObject* m_mMInstruct;
	SDL_Texture* m_mMLogo;




};

////////////////////////////////

class GameState : public State
{
public:

	static const int kPlayerSpeed = 300;
	std::vector<AnimatedSprite*> m_GameObjects;
	TiledLevel* m_pLevel;
	GameObject* m_Player;

	SDL_Texture* m_pPlayerTexture;
	SDL_Texture* m_pObjectTexture;
	SDL_Texture* m_backgroundTexture;

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
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;


};

////////////////////////////////

class WinScreen : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

////////////////////////////////

class LoseScreen : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};