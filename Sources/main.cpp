#include "MainWindow.h"

int main(int ac, char **av)
{
	int width = 1360;
	int height = 768;
	Fl::scheme("plastic");// plastic


	int tabsWidth = 300;
	Fl_Double_Window* wind = new Fl_Double_Window(100, 100, width, height, "Bloom Effect Demo");

	wind->begin();

	//menu
	//MainMenu* menu = new MainMenu(0, 0, width - tabsWidth, 30, &assets);

	//opengl Window
	MainWindow* gl = new MainWindow(0, 30, width - tabsWidth, height - 30/*, &graphics*/);
	wind->resizable(gl);

	//menu->drawer(gl);

	//side "properties" tabs
	//Fl_Tabs* tabs = new Fl_Tabs(width - tabsWidth, 0, tabsWidth, height);

	//LightingWindow* lightingEditor = new LightingWindow(tabs->x(), 30, tabs->w(), tabs->h() - 10);

	/*GameObjectEditor* GoEditor = new GameObjectEditor(tabs->x(), 30, tabs->w(), tabs->h() - 10, gl);
	tabs->add(GoEditor);
	tabs->add(lightingEditor);*/

	wind->end();

	//Scene scene(&assets);


	//scene.linkToUIComponent(GoEditor);
	//gl->setScene(&scene);
	//scene.setupIdle(gl);
	wind->show();
	Fl::run();
	delete wind;
	return 0;
}