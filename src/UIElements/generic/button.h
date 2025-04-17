#pragma once

#include "pane.h"
#include <SDL_pixels.h>
#include <functional>
#include <memory>

struct ButtonState {
	SDL_Color stateColor = {0x00, 0x00, 0x00, 0xff};
};

class Button : public Pane {
	private:
		int init();
		
	public:
		const static unsigned int NUM_STATES = 4;
		typedef enum {
			IDLE,
			HOVERED,
			CLICKED,
			DISABLED
		} State;

	protected:
		struct ButtonState states[NUM_STATES];
		State currentState = IDLE;
		std::function<void(std::weak_ptr<Pane>)> clickFn = [](std::weak_ptr<Pane> self){};

	public:

		Button();
		Button(int w, int h);
		Button(int x, int y, int w, int h);

		int init(SDL_Window *window, int flags) override;
		int init(SDL_Renderer *renderer) override;

		int tick(double deltaTime, IOHandler &io) override;

		int setBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
		int setBackgroundColor(State s, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);

		int setEnabled(bool value = false);
		int onClick(std::function<void(std::weak_ptr<Pane>)> fn);
};