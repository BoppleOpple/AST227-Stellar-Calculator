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
#include "camera.h"


Camera::Camera(){}

Camera::Camera(int* w, int* h){
	viewportWidth = w;
	viewportHeight = h;
	Camera();
}

int Camera::init(){
	if (linkedWindow == NULL) {
		fprintf(stderr, "Window was never defined.\n");
		return 1;
	}

	// create renderer tied to linkedWindow
	cameraRenderer = SDL_CreateRenderer(linkedWindow, -1, SDL_RENDERER_ACCELERATED);

	if (!cameraRenderer) {
		fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
		return 1;
	}

	return 0;
}

int Camera::tick(double deltaTime){
	return 0;
}

int Camera::render(){
	SDL_SetRenderDrawColor(cameraRenderer, 35, 30, 40, 255);
	SDL_RenderClear(cameraRenderer);

	// apply changes to canvas
	SDL_RenderPresent(cameraRenderer);
	return 0;
}

int Camera::attach(SDL_Window *window){
	linkedWindow = window;
	return 0;
}