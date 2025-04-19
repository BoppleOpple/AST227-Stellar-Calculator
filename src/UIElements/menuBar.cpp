#include "menuBar.h"
#include "generic/container.h"
#include <utility>

#define MENU_BAR_DEFAULT_WIDTH 200
#define MENU_BAR_DEFAULT_HEIGHT 50

MenuBar::MenuBar() : MenuBar(0, 0, MENU_BAR_DEFAULT_WIDTH, MENU_BAR_DEFAULT_HEIGHT) {}

int MenuBar::init(SDL_Window* window, int flags) {
	if ( Container::init(window, flags) ) return 1;
	return init();
}

int MenuBar::init(SDL_Renderer* renderer) {
	if ( Container::init(renderer) ) return 1;
	return init();
}

int MenuBar::init() {
	return 0;
}

int MenuBar::addPane(std::string name, std::shared_ptr<Pane> pane) {
	int width = pane->getRect()->w;

	(*pane).resize(width, paneRect.h);
	(*pane).move(nextPosition, 0);

	nextPosition += width;

	printf("%i\n", nextPosition);

	return Container::addPane(name, pane);
}

int MenuBar::removePane(std::string name) {
	std::shared_ptr<Pane> pane = getPane(name).lock();

	SDL_Rect *paneRect = (*pane).getRect();

	nextPosition -= paneRect->w;

	for (auto child : panes) {
		SDL_Rect *childRect = (*child.second).getRect();

		if (childRect->x >= paneRect->x) {
			(*child.second).move(childRect->x - paneRect->w, childRect->y);
		}
	}

	return Container::removePane(name);
}