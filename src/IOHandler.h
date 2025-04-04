#pragma once
// #include "controllable.h"

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
};