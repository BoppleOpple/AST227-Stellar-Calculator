#include "pane.h"
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <cstdio>

#define PANE_DEFAULT_WIDTH 100
#define PANE_DEFAULT_HEIGHT 100

Pane::Pane(){
	paneRect.x = 0;
	paneRect.y = 0;
	paneRect.w = PANE_DEFAULT_WIDTH;
	paneRect.h = PANE_DEFAULT_HEIGHT;
}

Pane::Pane(int w, int h) : Pane(){
	paneRect.w = w;
	paneRect.h = h;
}

Pane::Pane(int x, int y, int w, int h) : Pane(w, h){
	paneRect.x = x;
	paneRect.y = y;
}

int Pane::init(){
	if (linkedWindow == NULL) {
		fprintf(stderr, "Window was never defined.\n");
		return 1;
	}

	// create renderer tied to linkedWindow
	if (!paneRenderer)
		paneRenderer = SDL_CreateRenderer(linkedWindow, -1, SDL_RENDERER_TARGETTEXTURE);

	if (!paneRenderer) {
		fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
		return 1;
	}

	paneTexture = SDL_CreateTexture(
		paneRenderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		paneRect.w,
		paneRect.h
	);

	if (!paneTexture) {
		fprintf(stderr, "Texture could not be created: %s\n", SDL_GetError());
		return 1;
	}

	printf("%i, %i\n", paneRect.w, paneRect.h);

	SDL_SetRenderTarget(paneRenderer, paneTexture);
	SDL_SetTextureBlendMode(paneTexture, SDL_BLENDMODE_BLEND);

	return 0;
}

int Pane::tick(double deltaTime){
	return 0;
}

int Pane::render(){
	SDL_Texture *oldTarget = SDL_GetRenderTarget(paneRenderer);
	SDL_SetRenderTarget(paneRenderer, paneTexture);
	
	SDL_SetRenderDrawColor(paneRenderer, 255, 255, 255, 255);
	SDL_RenderClear(paneRenderer);

	SDL_SetRenderTarget(paneRenderer, oldTarget);
	return 0;
}

int Pane::attach(SDL_Window *window){
	linkedWindow = window;
	return 0;
}


SDL_Rect *Pane::getRect() {
	return &paneRect;
}