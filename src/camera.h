#include <SDL.h>
#include "gameObject.h"

class Camera : public GameObject {
	private:
		int* viewportWidth;
		int* viewportHeight;

	public:
		SDL_Window* linkedWindow = nullptr;
		SDL_Renderer* cameraRenderer = nullptr;
		
		Camera();
		Camera(int* w, int* h);

		int init() override; // initialises renderer
		int tick(double deltaTime) override;
		int render();

		int attach(SDL_Window* window);
};