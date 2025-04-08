#include "IOHandler.h"
#include <SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <memory>

class Pane : public std::enable_shared_from_this<Pane> {
	protected:
		SDL_Rect paneRect;
		std::weak_ptr<Pane> parent;

	public:
		SDL_Window* linkedWindow = nullptr;
		SDL_Renderer* paneRenderer = nullptr;
		SDL_Texture* paneTexture = nullptr;
		
		Pane();
		Pane(int w, int h);
		Pane(int x, int y, int w, int h);

		// initialises renderer
		int init(SDL_Window* window, int flags);
		int init(SDL_Renderer* renderer);

		int tick(double deltaTime, IOHandlerResponse *io);
		int render();


		int setParent(std::weak_ptr<Pane> parentPane);
		SDL_Rect *getRect();
		SDL_Point getGlobalPosition();
};