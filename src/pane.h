#include <SDL.h>
#include <SDL_render.h>

class Pane {
	private:
		int* viewportWidth;
		int* viewportHeight;

	public:
		SDL_Window* linkedWindow = nullptr;
		SDL_Renderer* paneRenderer = nullptr;
		SDL_Texture* paneTexture = nullptr;
		
		Pane();
		Pane(int* w, int* h);

		int init(); // initialises renderer
		int tick(double deltaTime);
		int render();

		int attach(SDL_Window* window);
};