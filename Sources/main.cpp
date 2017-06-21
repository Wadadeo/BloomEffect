#include "MainWindow.h"


struct BloomDebugInfo
{
	MainWindow*		window;
	BloomEffect*	bloom;
	eBloomDebug		toApply;
};

void debugBloom(Fl_Widget *widget, void* data)
{
	BloomDebugInfo* info = (BloomDebugInfo*)data;
	info->bloom->debug = info->toApply;
	info->window->redraw();
}


int main(int ac, char **av)
{
	int width = 1360;
	int height = 768;
	Fl::scheme("plastic");

	int tabsWidth = 300;
	Fl_Double_Window* wind = new Fl_Double_Window(100, 100, width, height, "Bloom Effect Demo");

	wind->begin();


	MainWindow* gl = new MainWindow(0, 30, width, height - 30);
	wind->resizable(gl);

	int buttonW = width / 4;

	BloomEffect *bloom = &(gl->graphicSystem()->bloomEffect());

	Fl_Button* complete = new Fl_Button(0, 0, buttonW, 30, "Scene with Bloom Effect");
	BloomDebugInfo completeInfo;
	completeInfo.window = gl;
	completeInfo.bloom = bloom;
	completeInfo.toApply = COMPLETE;
	complete->callback(debugBloom, &completeInfo);

	Fl_Button* normal = new Fl_Button(buttonW, 0, buttonW, 30, "Scene witout Bloom Effect");
	BloomDebugInfo normalInfo;
	normalInfo.window = gl;
	normalInfo.bloom = bloom;
	normalInfo.toApply = SCENE;
	normal->callback(debugBloom, &normalInfo);

	Fl_Button* bright = new Fl_Button(buttonW * 2, 0, buttonW, 30, "Scene bright areas");
	BloomDebugInfo brightInfo;
	brightInfo.window = gl;
	brightInfo.bloom = bloom;
	brightInfo.toApply = BRIGHT_ONLY;
	bright->callback(debugBloom, &brightInfo);

	Fl_Button* blurred = new Fl_Button(buttonW * 3, 0, buttonW, 30, "Blurred bright areas");
	BloomDebugInfo blurredInfo;
	blurredInfo.window = gl;
	blurredInfo.bloom = bloom;
	blurredInfo.toApply = BLURRED_BRIGHT;
	blurred->callback(debugBloom, &blurredInfo);

	wind->end();
	wind->show();
	Fl::run();

	delete wind;
	return 0;
}