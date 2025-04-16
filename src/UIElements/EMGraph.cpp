#include "EMGraph.h"
#include "../calculations.h"
#include <SDL_rect.h>
#include <SDL_render.h>

#define EM_GRAPH_DEFAULT_WIDTH 400
#define EM_GRAPH_DEFAULT_HEIGHT 100

EMGraph::EMGraph() : EMGraph(EM_GRAPH_DEFAULT_WIDTH, EM_GRAPH_DEFAULT_HEIGHT) {}
EMGraph::EMGraph(int w, int h) : EMGraph(0, 0, w, h) {}
EMGraph::EMGraph(int x, int y, int w, int h) : Pane(x, y, w, h) {
	updateVertices();
}

int EMGraph::tick(double deltaTime, IOHandler &io) {
	return 0;
}

int EMGraph::render() {
	if (!needsUpdate) return 0;

	SDL_Texture *oldTarget = SDL_GetRenderTarget(paneRenderer);
	SDL_SetRenderTarget(paneRenderer, paneTexture);

	if ( Pane::render() ) return 1;

	SDL_SetRenderDrawColor(paneRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderDrawLines(paneRenderer, verts.data(), verts.size());

	SDL_SetRenderTarget(paneRenderer, oldTarget);

	needsUpdate = false;
	return 0;
}

int EMGraph::setTemperature(int temp) {
	temperature = temp;
	return updateVertices();
}

int EMGraph::updateVertices() {
	verts.clear();
	for (int i = 0; i < numVerts; i++) {
		double progress = (double) i / (double) numVerts;

		SDL_Point newPoint = {
			(int) (paneRect.w * progress),
			paneRect.h - (int) (paneRect.h * (intensity(temperature, progress * maxWavelength) / maxIntensity))
		};

		verts.push_back(newPoint);

	}

	refresh();
	return 0;
}