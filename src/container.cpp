#include "container.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <map>

Container::Container() : Pane(){}
Container::Container(int w, int h) : Pane(w, h){}
Container::Container(int x, int y, int w, int h) : Pane(x, y, w, h){};

int Container::render() {
	SDL_Texture *oldTarget = SDL_GetRenderTarget(paneRenderer);
	SDL_SetRenderTarget(paneRenderer, paneTexture);

	std::map<std::string, Pane>::iterator iter;

	for (iter = panes.begin(); iter != panes.end(); iter++) {
		if ( iter->second.render() ) return 1;
		SDL_Rect *childRect = iter->second.getRect();
		SDL_RenderCopy(paneRenderer, iter->second.paneTexture, nullptr, childRect);
	}

	SDL_SetRenderTarget(paneRenderer, oldTarget);
	return 0;
}

int Container::addPane(std::string name, Pane pane) {
	panes.emplace(name, pane);

	return 0;
}

int Container::removePane(std::string name) {
	panes.erase(name);

	return 0;
}

Pane *Container::getPane(std::string name) {
	return &panes.find(name)->second;
}