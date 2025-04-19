#pragma once

#include "pane.h"
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>

class TextPane : public Pane {
	private:
		int init();
		int updateText();
	protected:
		std::string text = "Text";
		TTF_Font *font;
		SDL_Texture *textTexture;
		SDL_Color textColor = {0xff, 0xff, 0xff, 0xff};

		SDL_Rect textRect = {0, 0, 0, 0};

	public:
		using Pane::Pane;

		TextPane();

		int init(SDL_Window* window, int flags) override;
		int init(SDL_Renderer* renderer) override;

		int render() override;
};