#pragma once

#include "IOHandler.h"
#include <SDL.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <memory>
#include <string>

class Pane : public std::enable_shared_from_this<Pane> {
	protected:
		bool needsUpdate = true;
		SDL_Rect paneRect;
		std::weak_ptr<Pane> parent;
		SDL_Color backgroundColor = {0xff, 0xff, 0xff, 0xff};

	public:
		SDL_Window* linkedWindow = nullptr;
		SDL_Renderer* paneRenderer = nullptr;
		SDL_Texture* paneTexture = nullptr;
		std::string name = "Pane";
		
		Pane();
		Pane(int w, int h);
		Pane(int x, int y, int w, int h);

		// initialises renderer
		int init(SDL_Window* window, int flags);
		int init(SDL_Renderer* renderer);

		int refresh();

		virtual int tick(double deltaTime, IOHandler &io);
		virtual int render();

		int setBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		int setParent(std::weak_ptr<Pane> parentPane);
		SDL_Rect *getRect();
		SDL_Point getGlobalPosition();
};