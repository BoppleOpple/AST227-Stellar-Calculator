#pragma once

#include "generic/container.h"
#include <string>

class MenuBar : public Container {
	private:
		int init();

	protected:
		int nextPosition = 0;

	public:
		using Container::Container;
		
		MenuBar();

		int init(SDL_Window* window, int flags) override;
		int init(SDL_Renderer* renderer) override;

		int addPane(std::string name, std::shared_ptr<Pane>);
		int removePane(std::string name);
};