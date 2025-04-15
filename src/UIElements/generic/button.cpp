#include "button.h"
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <memory>

Button::Button() : Button(0, 0, 0, 0) {}
Button::Button(int w, int h) : Button(0, 0, w, h) {}
Button::Button(int x, int y, int w, int h) : Pane::Pane(x, y, w, h) {
	states[IDLE    ].stateColor = {0xaa, 0xaa, 0xaa, 0xff};
	states[HOVERED ].stateColor = {0x00, 0x00, 0x00, 0xff};
	states[CLICKED ].stateColor = {0x33, 0x33, 0x33, 0xff};
	states[DISABLED].stateColor = {0x11, 0x11, 0x11, 0xff};
}

int Button::tick(double deltaTime, IOHandler &io) {
	SDL_Point globalPos = getGlobalPosition();
	SDL_Point mousePos = io.getMousePosition();

	SDL_Rect globalRect = {
		globalPos.x,
		globalPos.y,
		paneRect.w,
		paneRect.h
	};

	State newState = currentState;

	if (SDL_PointInRect(&mousePos, &globalRect)) {
		newState = HOVERED;

		if (io.mouseButtonDown()) {
			clickFn(shared_from_this());
			newState = CLICKED;
		}
	} else {
		newState = IDLE;
	}
	
	if (newState == currentState) return 0;
	currentState = newState;

	SDL_Color c = states[currentState].stateColor;

	setBackgroundColor(c.r, c.g, c.b, c.a);

	refresh();

	return 0;
}

int Button::setBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	return Pane::setBackgroundColor(r, g, b, a);
}

int Button::setBackgroundColor(State s, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	states[s].stateColor = {r, g, b, a};
	return 0;
}

int Button::setEnabled(bool value) {
	currentState = (value) ? IDLE : DISABLED;
	return 0;
}

int Button::onClick(std::function<void(std::weak_ptr<Pane>)> fn) {
	clickFn = fn;
	return 0;
}