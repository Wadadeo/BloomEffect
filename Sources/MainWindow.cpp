#include "MainWindow.h"
#include <windows.h>

MainWindow::MainWindow(int x, int y, int w, int h)
	: Fl_Gl_Window(x, y, w, h)
{
	mode(FL_RGB | FL_ALPHA | FL_DOUBLE | FL_DEPTH | FL_STENCIL);
	contextInitialized = false;
	scene = new Scene(&_assets);
	_viewer = &(Viewer::main);
	_viewer->setAspectRatio(1.0f * (w / (float)h));
}

MainWindow::~MainWindow()
{
}

void MainWindow::initOpenGlContext()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "glewInit failed, aborting." << std::endl;
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	glViewport(0, 0, w(), h());
	contextInitialized = true;

}

/*void MainWindow::setScene(Scene * scene)
{
	_scene = scene;
	_viewer = &(Viewer::main);
	_viewer->setAspectRatio(1.0f * (w() / (float)h()));
}*/

GraphicsSystem * MainWindow::graphicSystem()
{
	return &_graphics;
}

void MainWindow::draw()
{	
	if (!contextInitialized) {
		initOpenGlContext(); //PAIN IN MY ASS : with FLTK, opengl context must be initialized here
		_assets.initEngineAssets();
		_graphics.init(w(), h(), &_assets);
		scene->load();
	}

	_graphics.update(0);
}

void MainWindow::resize(int x, int y, int w, int h)
{
	Fl_Gl_Window::resize(x, y, w, h);
	glViewport(0, 0, w, h);
}

int MainWindow::handle(int e)
{
	switch (e) {
	case FL_SHOW:
		show();
		return 1;
	case FL_PUSH:
	{
		m_pressedMouseButton = Fl::event_button();
		m_lastMouseX = Fl::event_x();
		m_lastMouseY = Fl::event_y();
	}
	damage(1);
	return 1;
	case FL_RELEASE:
	{
		m_pressedMouseButton = -1;
		damage(1);
		return 1;
	}
	case FL_DRAG: // if the user drags the mouse
	{
		if (!_viewer)
			return 0;
		double fractionChangeX = static_cast<double>(Fl::event_x() - m_lastMouseX) / static_cast<double>(this->w());
		double fractionChangeY = static_cast<double>(m_lastMouseY - Fl::event_y()) / static_cast<double>(this->h());
		if (m_pressedMouseButton == 1) {
			_viewer->rotate(fractionChangeX, fractionChangeY);
		}
		else if (m_pressedMouseButton == 2) {
			_viewer->zoom(fractionChangeY);
		}
		else if (m_pressedMouseButton == 3) {
			_viewer->translate(-fractionChangeX, -fractionChangeY,
				(Fl::event_key(FL_Shift_L) == 0) || (Fl::event_key(FL_Shift_R) == 0));
		}
		else {
			std::cout << "Warning: dragging with unknown mouse button!  Nothing will be done" << std::endl;
		}

		m_lastMouseX = Fl::event_x();
		m_lastMouseY = Fl::event_y();
		redraw();		
	}
	return 1;
	case FL_KEYBOARD:
		return 0;
	default:
		return 0;
	}
}

void MainWindow::askToRedraw()
{
	redraw();
}
