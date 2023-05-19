#define SDL_MAIN_HANDLED
#include <iostream>
#include <chrono>
#include "Game.h"


int main(int argc, char* argv[])
{
	SDL_SetMainReady();

	Game& myGameInstance = Game::GetInstance(); //everything that is taken from that class cannot be changed. so getting that instanace makes it exclusive to what is inside of it only.

	int result = myGameInstance.init("GAME 1017", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED); // so now we r init a window... to start it of sorts amnd get the window pos

	if (result == 0)
	{
		// Allocate a time_point outside that loop so that it is retained between frames. sorta like a clock
		auto lastFrameTime = std::chrono::high_resolution_clock::now();

		while (myGameInstance.IsRunning())
		{
			// Get current time_point.
			auto thisFrameTime = std::chrono::high_resolution_clock::now();

			// Subtract last frame's time_point from this frame's time_point to get the duration of the frame.
			std::chrono::duration<float> lastFrameDuration = thisFrameTime - lastFrameTime;

			// Convert the duration to a float
			float deltaTime = lastFrameDuration.count();

			// Don't forget to pass newFrameCounter into lastFrameCounter
			lastFrameTime = thisFrameTime;

			myGameInstance.HandleEvents(); //this is what we will call input.. usually it is called HandleEvents
			myGameInstance.Update(deltaTime);  //this is the update function
			myGameInstance.Render(); //this is the draw
		}
		myGameInstance.Clear(); //clearing SDL before you close the prog
	}

	return result;
}