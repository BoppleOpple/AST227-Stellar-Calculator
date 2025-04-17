#pragma once

#include <SDL.h>
#include <map>
#include <string>
#include "pane.h"

class Container : public Pane {
	protected:
		std::map<std::string, std::shared_ptr<Pane>> panes;

	public:
		Container();
		Container(int w, int h);
		Container(int x, int y, int w, int h);

		int tick(double deltaTime, IOHandler &io);
		int render();

		int addPane(std::string name, std::shared_ptr<Pane> pane);
		int removePane(std::string name);
		std::weak_ptr<Pane> getPane(std::string name);
};