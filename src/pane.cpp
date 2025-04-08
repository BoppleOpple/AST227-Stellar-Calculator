#include "pane.h"
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cstdio>
#include <memory>

#define PANE_DEFAULT_WIDTH 100
#define PANE_DEFAULT_HEIGHT 100

Pane::Pane(){
	parent = std::weak_ptr<Pane>();
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
int Pane::init(SDL_Renderer* renderer){
	if (renderer == NULL) {
		fprintf(stderr, "Renderer cannot be null.\n");
		return 1;
	}

	linkedWindow = SDL_RenderGetWindow(renderer);

	// create renderer tied to linkedWindow
	paneRenderer = renderer;

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

	SDL_Point position = getGlobalPosition();

	printf("Pane created with size %ix%i at global position (%i, %i)\n", paneRect.w, paneRect.h, position.x, position.y);

	SDL_SetRenderTarget(paneRenderer, paneTexture);
	SDL_SetTextureBlendMode(paneTexture, SDL_BLENDMODE_BLEND);

	return 0;
}

int Pane::init(SDL_Window* window, int flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE){
	if (window == NULL) {
		fprintf(stderr, "Window cannot be null.\n");
		return 1;
	}

	linkedWindow = window;

	// create renderer tied to linkedWindow
	paneRenderer = SDL_CreateRenderer(linkedWindow, -1, flags);

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

	printf("Pane created with size %ix%i\n", paneRect.w, paneRect.h);

	SDL_SetRenderTarget(paneRenderer, paneTexture);
	SDL_SetTextureBlendMode(paneTexture, SDL_BLENDMODE_BLEND);

	return 0;
}

int Pane::tick(double deltaTime, IOHandlerResponse *io){
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

int Pane::setParent(std::weak_ptr<Pane> parentPane) {
	if (parentPane.expired()) {
		printf("removing parent\n");
		parent.reset();
		return 0;
	}

	parent = parentPane;
	return 0;
}

SDL_Rect *Pane::getRect() {
	return &paneRect;
}

SDL_Point Pane::getGlobalPosition() {
	SDL_Point position = {paneRect.x, paneRect.y};

	if (!parent.expired()) {
		SDL_Point offset = parent.lock()->getGlobalPosition();
		position.x += offset.x;
		position.y += offset.y;
	}

	return position;
}