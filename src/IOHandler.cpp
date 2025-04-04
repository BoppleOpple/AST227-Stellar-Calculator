#include "IOHandler.h"
#include <SDL_events.h>

IOHandler::IOHandler(){}

IOHandlerResponse* IOHandler::handleEvents(){
	SDL_Event e;
	IOHandlerResponse* response = new IOHandlerResponse();
	response->quit = false;

	while ( SDL_PollEvent( &e ) ){
		switch (e.type) {
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				break;

			case SDL_KEYDOWN:
				printf("key %u pressed\n", e.key.keysym.scancode);
				break;

			case SDL_QUIT:
				response->quit = true;
				break;
			
			default:
				printf("unknown sdl event of type %u\n", e.type);
				break;
		}
	}
	
	return response;
}