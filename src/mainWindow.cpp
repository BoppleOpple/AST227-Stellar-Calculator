#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_mouse.h>
#include <SDL_render.h>
#include <cstdio>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <chrono>
#include <ctime>
#include "IOHandler.h"
#include "gameObject.h"
#include "mainWindow.h"

MainWindow::MainWindow() : Container(){}
MainWindow::MainWindow(int w, int h) : Container(w, h){}
MainWindow::MainWindow(int x, int y, int w, int h) : Container(x, y, w, h){}

int MainWindow::init(){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
		printf("sdl init error: %s\n", SDL_GetError());
		return 1;
	}
	printf("sdl didnt die \\o/\n");

	linkedWindow = SDL_CreateWindow(
		"Stellar Calculator",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		paneRect.w,
		paneRect.h,
		SDL_WINDOW_SHOWN
	);

	if (linkedWindow == NULL) {
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		return 1;
	}

	if ( Pane::init() ) return 1;

	SDL_SetRenderTarget(paneRenderer, nullptr);

	return 0;
}

int MainWindow::loop(){
	IOHandlerResponse* IOResponse = nullptr;
	std::chrono::time_point<std::chrono::system_clock> previousFrame = std::chrono::system_clock::now();
	Uint64 frame = 0;

	while (true){
		std::chrono::time_point<std::chrono::system_clock> currentFrame = std::chrono::system_clock::now();
		std::chrono::duration<double> frameTime = currentFrame - previousFrame;

		if ( tick( frameTime.count() ) ) return 1;
		if ( render() ) return 1;

		// printf("frame %llu (%lf ms | %u fps)\n", frame, frameTime.count() * 1000.0, (uint)(1.0/frameTime.count()));

		previousFrame = currentFrame;
		frame++;

		IOResponse = gIOHandler->handleEvents();

		if (IOResponse->quit) return 0;
	}
	return 0;
}

int MainWindow::tick(double deltaTime){
	return 0;
}

int MainWindow::render(){
	if (paneRenderer == nullptr) return 1;

	SDL_SetRenderDrawColor(paneRenderer, 35, 30, 40, 255);
	SDL_RenderClear(paneRenderer);



	// apply changes to canvas
	SDL_RenderPresent(paneRenderer);
	return 0;
}

int MainWindow::exit(){
	SDL_DestroyWindow( linkedWindow );

	printf("exit\n");

	SDL_Quit();

	return 0;
}