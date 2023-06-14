#pragma once
#include <iostream>
#include <string>
#include <map>
#include <SDL_mixer.h>

class Soundmanager
{
public: 
	static bool Init();

	static bool LoadMusic(const std::string& file_name, const std::string& id);
	static void UnloadMusic(const std::string& id);
	static void PlayMusic(const std::string& id, int loop = -1, int fade_in = 0);
	static void StopMusic(int fade_out = 0);
	static void PauseMusic();
	static void ResumeMusic();
	static void SetMusicVolume(const int vol);

	static bool LoadSound(const std::string& file_name, const std::string& id);
	static void UnloadSound(const std::string& id);
	static void PlaySound(const std::string& id, int loop = 0, int channel = -1);
	static void StopSound(int channel = -1);
	static void SetSoundVolume(const int vol, int channel = -1);

	static void SetAllVolume(const int vol);

	static void Quit();

private:

	static std::map<std::string, Mix_Chunk*> s_sfxs;
	static std::map<std::string, Mix_Music*> s_music;


private:
	Soundmanager();


};

