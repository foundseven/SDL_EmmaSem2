#include "TextureManager.h"

#include "TextureManager.h"
#include "Game.h"

#include <iostream>

std::map<std::string, SDL_Texture*> TextureManager::s_textures;

void TextureManager::Load(const char* path, const std::string key)
{
	SDL_Texture* temp = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path);
	if (temp == nullptr)
	{
		std::cout << "Could not load texture! " << IMG_GetError() << std::endl;
	}
	else
	{
		s_textures.emplace(key, temp); // add to the map
		std::cout << "Successfully Loaded! " << key << std::endl;
	}
}

void TextureManager::Unload(const std::string key)
{

	if (s_textures.find(key) != s_textures.end())
	{
		SDL_DestroyTexture(s_textures[key]); //deallocates the texture
		s_textures.erase(key); //removes the texture ptr from map
	}
	else
	{
		std::cout << "could not unload! " << key << " - not found. " << std::endl;
	}
}

SDL_Texture* TextureManager::GetTexture(const std::string key)
{
	return s_textures[key];
}

void TextureManager::Quit()
{
	for (auto const& i : s_textures)
	{
		SDL_DestroyTexture(s_textures[i.first]);
	}
	s_textures.clear();
}