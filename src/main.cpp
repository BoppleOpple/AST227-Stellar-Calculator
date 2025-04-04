#include "mainWindow.h"
#include "IOHandler.h"

MainWindow game;
IOHandler globalIOHandler;

int main(int argc, char* args[]){
	globalIOHandler = IOHandler();
	game = MainWindow();

	if (game.init()) return 1;

	game.gIOHandler = &globalIOHandler;


	if (game.loop()) return 1;
	if (game.exit()) return 1;
	return 0;
}