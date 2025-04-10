#include "button.h"
#include <SDL_rect.h>

Button::Button() : Pane::Pane() {}
Button::Button(int w, int h) : Pane::Pane(w, h) {}
Button::Button(int x, int y, int w, int h) : Pane::Pane(x, y, w, h) {}

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
	} else {
		newState = IDLE;
	}
	
	if (newState == currentState) return 0;
	currentState = newState;


	switch (currentState) {
		case IDLE:
			setBackgroundColor(0x00, 0x00, 0x00, 0xff);
			break;

		case HOVERED:
			setBackgroundColor(0xaa, 0xaa, 0xaa, 0xff);
			break;
		
		default:
			break;
	}

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