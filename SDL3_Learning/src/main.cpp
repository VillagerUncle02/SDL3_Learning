#include <stdio.h>
#include <vector>


#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_opengl.h>

#include "MarcoLib.h"
#include "PointsExample.h"
#include "RectangleExample.h"

int main(int argc, char* argv[])
{
	//Initialization

	//SDL Initialization

	//Set App Meta Data
	if (!SDL_SetAppMetadata("SDL App Metadata", "0.01", NULL))
		SDL_Log(SDL_GetError());
	
	printf("This is a C style cmd char* type output \n");

	//Initialize SDL library
	if (!SDL_Init(SDL_INIT_VIDEO))
		SDL_Log(SDL_GetError());
	
	//Create window and renderer,then setup properties of them
	SDL_Window* window = SDL_CreateWindow("SDL3 Project", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL );
	if (window == nullptr)
	{
		SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
		SDL_Quit();
		return SDL_APP_FAILURE;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == nullptr)
	{
		SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return SDL_APP_FAILURE;
	}

	SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);

	SDL_SetRenderVSync(renderer, true);
	
	bool quit = false;

	static Uint64 last_time = SDL_GetTicksNS();

	SDL_FRect rectangle = { 0.0f, WINDOW_CENTER_Y - 25.0f, 50.0f, 50.0f };
	SDL_FRect scaleRectangle = { 50.0f, 50.0f, 10.0f, 10.0f };
	std::vector<SDL_FRect> scaleRectangles;
	for (int i = 0; i < 3; i++)
	{
		scaleRectangles.push_back({ 310.0f - i * 5.0f, 200.0f - i * 5.0f, 10.0f + i * 10.0f, 10.0f + i * 10.0f });
	}
	bool scaleRectangleFlag = true;
	float scaleSpeed = 1.0f;
	float maxScale = 100.0f;
	float minScale = 10.0f;

	PointsExample pointExample(NUMS_POINTS, WINDOW_WIDTH, WINDOW_HEIGHT);

	float FPS = 0.0f;
	float fpsUpdateTimer = 0.0;

	//main loop
	while (!quit)
	{
		SDL_Event event;

		//calculate delta time from last loop
		const Uint64 now = SDL_GetTicksNS();
		double deltaTime = (now - last_time) / NS_PER_SECOND;
		if (deltaTime > 0.1) deltaTime = 0.1;  //avoid debug pause cause fatal error
		fpsUpdateTimer += (float)deltaTime;

		//Is app quit?
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT) quit = true;
		}
		last_time = now;

		if (fpsUpdateTimer >= 0.5)
		{
			printf("FPS %.0f \n", 1.0 / deltaTime);
			fpsUpdateTimer = 0.0;
		}

		rectangle.x <= 590 ? rectangle.x += (float)(deltaTime * 50.0) : rectangle.x = 0.0f;

		pointExample.UpdatePoints((float)deltaTime);

		if (scaleRectangleFlag)
		{
			scaleRectangle.h += scaleSpeed;
			scaleRectangle.w += scaleSpeed;

			for (int i = 0; i < scaleRectangles.size(); i++)
			{
				scaleRectangles[i].x -= scaleSpeed * (i + 1) / 2.0f;
				scaleRectangles[i].y -= scaleSpeed * (i + 1) / 2.0f;
				scaleRectangles[i].h += scaleSpeed * (i + 1);
				scaleRectangles[i].w += scaleSpeed * (i + 1);
			}

			if (scaleRectangle.h >= maxScale) scaleRectangleFlag = false;
		}
		else
		{
			scaleRectangle.h -= scaleSpeed;
			scaleRectangle.w -= scaleSpeed;

			for (int i = 0; i < scaleRectangles.size(); i++)
			{
				scaleRectangles[i].x += scaleSpeed * (i + 1) / 2.0f;
				scaleRectangles[i].y += scaleSpeed * (i + 1) / 2.0f;
				scaleRectangles[i].h -= scaleSpeed * (i + 1);
				scaleRectangles[i].w -= scaleSpeed * (i + 1);
			}

			if (scaleRectangle.h <= minScale) scaleRectangleFlag = true;
		}

		//Render
		//background color

		

		SDL_SetRenderDrawColor(renderer, (Uint8)100, (Uint8)100, (Uint8)100, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		pointExample.Render(renderer);

		SDL_SetRenderDrawColor(renderer, (Uint8)0, (Uint8)255, (Uint8)0, SDL_ALPHA_OPAQUE);
		SDL_RenderRect(renderer, &rectangle);

		SDL_SetRenderDrawColor(renderer, (Uint8)255, (Uint8)0, (Uint8)0, SDL_ALPHA_OPAQUE);
		SDL_RenderRect(renderer, &scaleRectangle);
		SDL_SetRenderDrawColor(renderer, (Uint8)255, (Uint8)0, (Uint8)0, SDL_ALPHA_OPAQUE);
		SDL_RenderRects(renderer, scaleRectangles.data(), (int)scaleRectangles.size());

		SDL_RenderPresent(renderer);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}


