#pragma once

#include <string>
#include "sdl_2\SDL.h"

using namespace std;

class Display
{

public:
	Display(int width, int height, const string title);
	virtual ~Display();

	void Clear(float r, float g, float b, float a);
	void Clear();
	void Update();
	bool IsCloseRequested();

private:

	SDL_Window* window;
	SDL_GLContext context;
	bool isClosed;

};

