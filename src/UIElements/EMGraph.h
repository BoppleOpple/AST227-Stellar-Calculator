#pragma once

#include "generic/pane.h"
#include <SDL_rect.h>
#include <vector>

class EMGraph : public Pane {
	protected:
		int temperature = 5800;
		int numVerts = 100;

		double minWavelength = 0.0;
		double maxWavelength = 3.0e-6;
		double minIntensity = 0.0;
		double maxIntensity = 1.0e5;

		std::vector<SDL_Point> verts;

	public:
		using Pane::Pane;
		
		EMGraph();
		EMGraph(int w, int h);
		EMGraph(int x, int y, int w, int h);

		int tick(double deltaTime, IOHandler &io);
		int render();

		int setTemperature(int temp);
		int updateVertices();
};