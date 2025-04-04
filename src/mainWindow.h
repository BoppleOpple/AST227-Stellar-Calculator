#include <SDL.h>
#include <list>
#include "camera.h"
#include "IOHandler.h"
#include "gameObject.h"

class MainWindow {
	private:
		int width = 800;
		int height = 600;
		std::list<GameObject*> gameObjects;
		
	public:
		SDL_Window* gWindow = nullptr;
		Camera* activeCamera = nullptr;
		IOHandler* gIOHandler = nullptr;
		
		MainWindow();

		int init();                 // initialises renderer and such
		int loop();                 // outer loop function, handles exceptions/events and organizwes exec order
		int tick(double deltaTime); // update game objects
		int render();               // renders scene
		int exit();                 // safely exits

		int addGameObject(GameObject* o);
		int addCamera(Camera* c);
};