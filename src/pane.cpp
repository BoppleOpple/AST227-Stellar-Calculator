#include "pane.h"

Pane::Pane(){}

Pane::Pane(int* w, int* h){
	viewportWidth = w;
	viewportHeight = h;
	Pane();
}

int Pane::init(){
	if (linkedWindow == NULL) {
		fprintf(stderr, "Window was never defined.\n");
		return 1;
	}

	// create renderer tied to linkedWindow
	paneRenderer = SDL_CreateRenderer(linkedWindow, -1, SDL_RENDERER_ACCELERATED);

	if (!paneRenderer) {
		fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
		return 1;
	}

	return 0;
}

int Pane::tick(double deltaTime){
	return 0;
}

int Pane::render(){
	SDL_SetRenderDrawColor(paneRenderer, 35, 30, 40, 255);
	SDL_RenderClear(paneRenderer);

	// apply changes to canvas
	SDL_RenderPresent(paneRenderer);
	return 0;
}

int Pane::attach(SDL_Window *window){
	linkedWindow = window;
	return 0;
}