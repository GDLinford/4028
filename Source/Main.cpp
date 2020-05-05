#include <stdafx.h>
#include "Renderer.h"
#include "Console.h"
#include "rc_ImageLoader.h"
#include "rc_TextureManager.h"
#include "InputManager.h"
#include "Player.h"
#include "map.h"

void drawBackground(Renderer& a_renderer)
{
	unsigned int ceilingColour = 0x00505050;
	unsigned int floorColour = 0x00B2B2B2;
	a_renderer.FillRenderBuffer(0, 0, 640, 320, ceilingColour);
	a_renderer.FillRenderBuffer(0, 320, 640, 320, floorColour);
}

int main(int argc, char* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);


	//Set up the console for the application
	Console console;
	console.Initialise("Raycaster Console");

	Map map;
	if (map.LoadMap("../resources/Maps/Map.map"))
	{
		//Create a render context window - or bitmap rendeer window
		u32 windowWidth = 640;
		u32 WindowHeight = 676;

		TextureManager texMan;
		InputManager::CreateInstance();

		Renderer mainWindow;
		if (!mainWindow.Initialise(console.GetConsoleWindowHandle(), windowWidth, WindowHeight))
		{
			Player player;

			MSG msg = { 0 };

			//Create a timer, with current time and previous time to get delta time between frames
			auto currentTime = std::chrono::high_resolution_clock::now();
			auto previousTime = currentTime;

			//delta time variable
			std::chrono::duration<double> elapsedTime;

			unsigned int frame = 0;

			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{

					previousTime = currentTime;
					currentTime = std::chrono::high_resolution_clock::now();
					elapsedTime = currentTime - previousTime;
					double fElapsedTime = elapsedTime.count();

					player.Update((float)fElapsedTime);
					mainWindow.ClearRenderBuffer();
					drawBackground(mainWindow);

					map.draw(&player);

					mainWindow.Draw();
					if (frame % 30 == 0)
					{
						//buffer to hold FPS value
						wchar_t fpsBuffer[8];
						unsigned int fps = (unsigned int)(1.0f / fElapsedTime);
						//swprintf_s -- adds a null terminator at n-1, saves us doing it manually
						//Due to this, buffer to be an additional wchar_t longer
						//Using a ternary to limit fps display to 999 if over 1000 as not enough characters in buffer
						//to display more than this, and 999 is plenty fast as demonstraited here:https://images.app.goo.gl/jdjP15BqXckZtmtu9
						swprintf_s(fpsBuffer, 8, L"FPS=%3u", fps > 999 ? 999 : fps);
						console.WriteToLocation(fpsBuffer, 8, 0, 0);
					}
					++frame;
				}
			}
		}
		return 0;
	}
}
