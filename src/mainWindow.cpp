#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_mouse.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <cstdio>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <chrono>
#include <ctime>
#include <thread>
#include "IOHandler.h"
#include "gameObject.h"
#include "mainWindow.h"

#define MAIN_WINDOW_DEFAULT_WIDTH 600
#define MAIN_WINDOW_DEFAULT_HEIGHT 400

#define FPS 60
#define FRAME_DURATION_S 1.0 / (double) FPS

MainWindow::MainWindow() : Container(MAIN_WINDOW_DEFAULT_WIDTH, MAIN_WINDOW_DEFAULT_HEIGHT){}
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

	// if ( Container::init() ) return 1;

	paneRenderer = SDL_CreateRenderer(linkedWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);

	Pane *newPane = new Pane(paneRect.w/2 - 50, paneRect.h/2 - 50, 100, 100);

	newPane->attach(linkedWindow);
	newPane->paneRenderer = paneRenderer;

	newPane->init();

	addPane("new pane", *newPane);

	return 0;
}

int MainWindow::loop(){
	IOHandlerResponse* IOResponse = nullptr;
	Uint64 frame = 0;
	Uint32 frameTime = 0;

	while (true){
		Uint64 startFrame = SDL_GetTicks64();

		if ( tick( frameTime ) ) return 1;
		if ( render() ) return 1;

		// apply changes to canvas
		SDL_RenderPresent(paneRenderer);
		

		Uint64 endFrame = SDL_GetTicks64();
		frameTime = endFrame - startFrame;

		// printf("rendered frame %llu in %u ms\n", frame, frameTime);

		IOResponse = gIOHandler->handleEvents();

		if (IOResponse->quit) return 0;


		frame++;
		// Uint32 sleepTime = SDL_max(FRAME_DURATION_S * 1000 - frameTime, 0);
		// SDL_Delay(sleepTime);

		endFrame = SDL_GetTicks64();
		frameTime = endFrame - startFrame;

		printf("frame %llu (%u ms | %u fps)\n", frame, frameTime, 1000/frameTime);
	}
	return 0;
}

int MainWindow::tick(double deltaTime){
	return 0;
}

int MainWindow::render(){
	if (paneRenderer == nullptr) return 1;
	SDL_Texture *oldTarget = SDL_GetRenderTarget(paneRenderer);
	SDL_SetRenderTarget(paneRenderer, paneTexture);

	SDL_SetRenderDrawColor(paneRenderer, 35, 30, 40, 255);
	SDL_RenderClear(paneRenderer);

	Container::render();

	SDL_SetRenderTarget(paneRenderer, oldTarget);
	return 0;
}

int MainWindow::exit(){
	SDL_DestroyWindow( linkedWindow );

	printf("exit\n");

	SDL_Quit();

	return 0;
}