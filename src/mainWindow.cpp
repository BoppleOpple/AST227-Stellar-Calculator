#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_mouse.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <cstddef>
#include <cstdio>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <chrono>
#include <ctime>
#include <memory>
#include <new>
#include <thread>
#include "IOHandler.h"
#include "container.h"
#include "mainWindow.h"
#include "button.h"

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

	if ( Container::init(linkedWindow, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC) ) return 1;

	name = "main window";
	
	std::shared_ptr<Container> newContainer = std::make_shared<Container>(paneRect.w/2 - 100, paneRect.h/2 - 100, 200, 200);

	std::shared_ptr<Button> newPane = std::make_shared<Button>(50, 50, 100, 100);
	newPane->setBackgroundColor(0xff, 0x90, 0x60, 0xff);

	addPane("new container", newContainer);
	newContainer->addPane("new pane", newPane);
	
	newContainer->init(paneRenderer);
	newPane->init(paneRenderer);
	
	paneTexture = nullptr;

	setBackgroundColor(0x33, 0x33, 0x33, 0xff);

	return 0;
}

int MainWindow::tick(double deltaTime, IOHandler &io) {
	return Container::tick(deltaTime, io);
}

int MainWindow::loop(IOHandler &gIOHandler){
	IOHandlerResponse* IOResponse = nullptr;
	Uint64 frame = 0;
	Uint32 frameTime = 0;

	while (true){
		Uint64 startFrame = SDL_GetTicks64();

		IOResponse = gIOHandler.handleEvents();
		if (IOResponse->quit) return 0;

		if ( tick( frameTime, gIOHandler ) ) return 1;

		if (needsUpdate) {
			if ( render() ) return 1;

			// apply changes to canvas
			SDL_RenderPresent(paneRenderer);
		}
		

		Uint64 endFrame = SDL_GetTicks64();
		frameTime = endFrame - startFrame;

		// printf("rendered frame %llu in %u ms\n", frame, frameTime);

		frame++;
		// Uint32 sleepTime = SDL_max(FRAME_DURATION_S * 1000 - frameTime, 0);
		// SDL_Delay(sleepTime);

		endFrame = SDL_GetTicks64();
		frameTime = endFrame - startFrame;

		// printf("frame %llu (%u ms | %u fps)\n", frame, frameTime, 1000/frameTime);
	}
	return 0;
}

int MainWindow::exit(){
	SDL_DestroyWindow( linkedWindow );

	printf("exit\n");

	SDL_Quit();

	return 0;
}