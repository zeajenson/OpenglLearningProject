#pragma once

#include <SDL2\SDL.h>
class Display
{
public:
	Display();
	Display(int width, int height,const char * title);
	virtual~Display();

	void clear(float r, float g, float b, float a);
	void update();

	int getWidth(void);
	int getHeight(void);

	bool isClosed();
protected:
private:
	Display(const Display&other) {}
	Display& operator =(const Display & other) {}

	SDL_Window * mainWindow;
	SDL_GLContext  mainGLContext;
	bool mainIsClosed;

	int width, height;
};

