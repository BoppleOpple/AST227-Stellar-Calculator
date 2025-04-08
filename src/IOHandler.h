#pragma once

#include <SDL_rect.h>
struct IOHandlerResponse {
	bool quit = false;
};

class IOHandler {
	private:
		int mouseX;
		int mouseY;

		// Controllable* boundObject = nullptr;
	public:
		IOHandler();

		IOHandlerResponse* handleEvents();
		SDL_Point getMousePosition(SDL_Point offset);
};