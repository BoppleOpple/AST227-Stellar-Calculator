#include "button.h"
#include "pane.h"
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <memory>

#define BUTTON_DEFAULT_WIDTH 100
#define BUTTON_DEFAULT_HEIGHT 50

Button::Button() : Button(0, 0, BUTTON_DEFAULT_WIDTH, BUTTON_DEFAULT_HEIGHT) {}
Button::Button(int w, int h) : Button(0, 0, w, h) {}
Button::Button(int x, int y, int w, int h) : Pane::Pane(x, y, w, h) {
	states[IDLE    ].stateColor = {0x00, 0x00, 0x00, 0xff};
	states[HOVERED ].stateColor = {0x22, 0x22, 0x22, 0xff};
	states[CLICKED ].stateColor = {0x33, 0x33, 0x33, 0xff};
	states[DISABLED].stateColor = {0xaa, 0xaa, 0xaa, 0xff};
}

int Button::init() {
	setBackgroundColor(
		states[currentState].stateColor.r,
		states[currentState].stateColor.g,
		states[currentState].stateColor.b,
		states[currentState].stateColor.a
	);

	return 0;
}

int Button::init(SDL_Window *window, int flags) {
	if ( Pane::init(window, flags) ) return 1;
	return init();
};
int Button::init(SDL_Renderer *renderer) {
	if ( Pane::init(renderer) ) return 1;
	return init();
};

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
			newState = CLICKED;
		}
	} else {
		newState = IDLE;
	}
	
	if (newState == currentState) return 0;
	currentState = newState;

	if (currentState == CLICKED) clickFn(shared_from_this());

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