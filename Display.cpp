#include "Display.h"
#include <Windows.h>
#include <iostream>
#include <GL\glew.h>


Display::Display()
{
}

Display::Display(int width, int height, const char* title) {
	//init sdl
	this->width = width;
	this->height = height;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);		// 8 bits of red data
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);		// 8 bits of green data
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);		// 8 bits of blue data
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);		//8 bits of alpha data
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);	//because we have 32 bits total
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);		// allocate space for z buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	//allocate double buffer for rendering

	mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	SDL_SetWindowBordered(mainWindow, SDL_TRUE);
	mainGLContext = SDL_GL_CreateContext(mainWindow); //create context for window to use graphics cardd through opengl

	GLenum status = glewInit();
	if (status != GLEW_OK)std::cerr << "glew faild to initialize"<< std::endl; //test if glew initalized

	mainIsClosed = false;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


Display::~Display()
{					//Destroy 
	SDL_GL_DeleteContext(mainGLContext);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();	
}

void Display::clear(float r, float g, float b, float a) { //clear the display
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

bool Display::isClosed() {
	return mainIsClosed;
}

void Display::update() {
	SDL_GL_SwapWindow(mainWindow);

	SDL_Event e;
	while (SDL_PollEvent(&e)) { //test if the operating system tells the program to crass
		if (e.type == SDL_QUIT)
			mainIsClosed = true;
	}
}

int Display::getWidth(void) {
	return this->width;
}

int Display::getHeight(void) {
	return this->height;
}