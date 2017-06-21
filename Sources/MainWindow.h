#pragma once

#include <iostream>
#include <string>
#include <list>

#include "GL/glew.h"
#include <GL/gl.h>

#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <FL\Fl_Double_Window.H>
#include <FL\Fl_Value_Slider.H>
#include <FL\Fl_Box.H>
#include <FL\Fl_Color_Chooser.H>
#include <FL\Fl_Tabs.H>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

#include "IDrawer.h"
#include "Viewer.h"
#include "GraphicsSystem.h"
#include "AssetCatalogue.h"
#include "Scene.h"

class MainWindow : public Fl_Gl_Window, public IDrawer
{
private:
	Viewer*			_viewer;
	Scene*			scene;
	AssetCatalogue	_assets;
	GraphicsSystem	_graphics;

	bool contextInitialized;

	int m_pressedMouseButton;
	int m_lastMouseX;
	int m_lastMouseY;

public:

	//Clock	clock;
	MainWindow(int x, int y, int w, int h/*, GraphicsSystem *graphics*/);
	~MainWindow();
	void initOpenGlContext();
	//void setScene(Scene *scene);

	GraphicsSystem * graphicSystem();

protected:
	void draw();
	void resize(int, int, int, int);
	int handle(int);

	// Inherited via IDrawer
	virtual void askToRedraw();
};

