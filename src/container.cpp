#include "container.h"
#include <map>

Container::Container() : Pane(){}
Container::Container(int w, int h) : Pane(w, h){}
Container::Container(int x, int y, int w, int h) : Pane(x, y, w, h){};

int Container::render() {
	if ( Pane::render() ) return 1;

	std::map<std::string, Pane>::iterator iter;

	for (iter = panes.begin(); iter != panes.end(); iter++)
		if ( iter->second.render() ) return 1;

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