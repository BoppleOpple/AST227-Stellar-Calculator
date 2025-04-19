#include "textPane.h"
#include "pane.h"
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <cstdio>

#define TEXT_PANE_DEFAULT_WIDTH 100
#define TEXT_PANE_DEFAULT_HEIGHT 30

TextPane::TextPane() : TextPane(0, 0, TEXT_PANE_DEFAULT_WIDTH, TEXT_PANE_DEFAULT_HEIGHT) {}

int TextPane::init() {
	font = TTF_OpenFont("./res/ProggyClean.ttf", 24);
	
	return updateText();
}

int TextPane::init(SDL_Window* window, int flags) {
	if ( Pane::init(window, flags) ) return 1;
	return init();
}

int TextPane::init(SDL_Renderer* renderer) {
	if ( Pane::init(renderer) ) return 1;
	return init();
}

int TextPane::updateText() {
	SDL_DestroyTexture(textTexture);

	TTF_SizeText(font, text.c_str(), &textRect.w, &textRect.h);

	textTexture = SDL_CreateTextureFromSurface(
		paneRenderer,
		TTF_RenderText_Solid(font, text.c_str(), textColor)
	);

	

	return 0;
}

int TextPane::render() {
	if (!needsUpdate) return 0;

	SDL_Texture *oldTarget = SDL_GetRenderTarget(paneRenderer);
	SDL_SetRenderTarget(paneRenderer, paneTexture);

	Pane::render();

	SDL_RenderCopy(paneRenderer, textTexture, nullptr, &textRect);

	SDL_SetRenderTarget(paneRenderer, oldTarget);

	needsUpdate = false;
	return 0;
}