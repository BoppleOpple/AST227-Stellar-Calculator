#pragma once

#include <SDL.h>
#include <list>
#include "../IOHandler.h"
#include "generic/container.h"

class MainWindow : public Container {
	private:
		void addMenuBar();
		void addEMGraph();
	public:
		using Container::Container;

		MainWindow();

		int init(); // initialises renderer and such
		int tick(double deltaTime, IOHandler &io);
		int loop(IOHandler &gIOHandler); // outer loop function, handles exceptions/events and organizwes exec order
		int exit(); // safely exits
};