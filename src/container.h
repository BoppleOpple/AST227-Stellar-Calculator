#include <SDL.h>
#include <map>
#include <string>
#include "pane.h"

class Container : public Pane {
	protected:
		std::map<std::string, Pane> panes;

	public:
		Container();
		Container(int w, int h);
		Container(int x, int y, int w, int h);

		int render();

		int addPane(std::string name, Pane pane);
		int removePane(std::string name);
		Pane *getPane(std::string name);
};