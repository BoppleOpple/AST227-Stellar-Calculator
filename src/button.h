#pragma once

#include "pane.h"
#include <SDL_pixels.h>

struct ButtonState {
	SDL_Color stateColor = {0x00, 0x00, 0x00, 0xff};
};

class Button : public Pane {
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

	public:

		Button();
		Button(int w, int h);
		Button(int x, int y, int w, int h);

		int tick(double deltaTime, IOHandler &io);

		int setBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
		int setBackgroundColor(State s, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
};