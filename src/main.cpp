#include "mainWindow.h"
#include "IOHandler.h"

MainWindow game;
IOHandler globalIOHandler;
Camera defaultCamera;

int main(int argc, char* args[]){
	globalIOHandler = IOHandler();
	game = MainWindow();
	defaultCamera = Camera();

	if (game.init()) return 1;

	game.gIOHandler = &globalIOHandler;

	game.addCamera(&defaultCamera);
	game.activeCamera = &defaultCamera;

	if (game.loop()) return 1;
	if (game.exit()) return 1;
	return 0;
}