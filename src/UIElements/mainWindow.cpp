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
#include "../IOHandler.h"
#include "generic/container.h"
#include "generic/button.h"
#include "mainWindow.h"
#include "EMGraph.h"
#include "menuBar.h"

#define MAIN_WINDOW_DEFAULT_WIDTH 600
#define MAIN_WINDOW_DEFAULT_HEIGHT 400

#define FPS 60
#define FRAME_DURATION_S 1.0 / (double) FPS

MainWindow::MainWindow() : MainWindow(MAIN_WINDOW_DEFAULT_WIDTH, MAIN_WINDOW_DEFAULT_HEIGHT){}

int MainWindow::init(){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
		printf("sdl init error: %s\n", SDL_GetError());
		return 1;
	}
	printf("sdl didnt die \\o/\n");

	if (TTF_Init()){
		printf("ttf init error: %s\n", TTF_GetError());
		return 1;
	}
	printf("ttf didnt die \\o/\n");

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

	addMenuBar();
	addEMGraph();
	
	paneTexture = nullptr;
	setBackgroundColor(0x33, 0x33, 0x33, 0xff);

	return 0;
}

void MainWindow::addMenuBar() {
	const int menuBarHeight = 30;

	std::shared_ptr<MenuBar> menu = std::make_shared<MenuBar>(0, 0, paneRect.w, menuBarHeight);
	menu->setBackgroundColor(0x00, 0x50, 0x00, 0xff);

	menu->init(paneRenderer);


	std::shared_ptr<Button> mainScreenButton = std::make_shared<Button>();
	mainScreenButton->init(paneRenderer);
	mainScreenButton->onClick([](std::weak_ptr<Pane> self){
		Button *buttonSelf = dynamic_cast<Button*>(self.lock().get());

		printf("CLICK\n");
	});

	menu->addPane("main button", mainScreenButton);

	std::shared_ptr<Button> variablesButton = std::make_shared<Button>();
	variablesButton->init(paneRenderer);

	menu->addPane("variables button", variablesButton);

	addPane("menu bar", menu);
}

void MainWindow::addEMGraph() {
	const int radiationPaneHeight = 50;

	std::shared_ptr<EMGraph> radiationPane = std::make_shared<EMGraph>(0, paneRect.h - radiationPaneHeight, paneRect.w, radiationPaneHeight);
	radiationPane->setBackgroundColor(0x00, 0x00, 0x00, 0xff);

	radiationPane->init(paneRenderer);
	addPane("blackbody radiation graph", radiationPane);
}

int MainWindow::tick(double deltaTime, IOHandler &io) {
	// EMGraph *radiationPane = dynamic_cast<EMGraph*>(getPane("blackbody radiation graph").lock().get());

	// if (radiationPane != nullptr) {
	// 	radiationPane->setTemperature(100 * io.getMousePosition().x);
	// }

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