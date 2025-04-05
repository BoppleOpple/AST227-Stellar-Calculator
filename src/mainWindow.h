#include <SDL.h>
#include <list>
#include "IOHandler.h"
#include "container.h"

class MainWindow : public Container {
	public:
		IOHandler* gIOHandler = nullptr;
		
		MainWindow();
		MainWindow(int w, int h);
		MainWindow(int x, int y, int w, int h);

		int init();                 // initialises renderer and such
		int loop();                 // outer loop function, handles exceptions/events and organizwes exec order
		int tick(double deltaTime); // update game objects
		int render();               // renders scene
		int exit();                 // safely exits
};