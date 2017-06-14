#include "display.h"
#include <GL/glew.h>
#include <iostream>
Display::Display(int width, int height, const std::string& title)	// Constructor - Width/Height of the window, title of window
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);	// How much red bits are allowed - minimum 
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);	// How much green bits are allowed - minimum 
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);	// How much blue bits are allowed - minimum 
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);	// How much transparency bits are allowed - minimum 
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);// How much memory buffer size allowed - 32 bits CHECK THIS
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// How much memory buffer size allowed - 32 bits CHECK THIS
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);// Whether to use a double buffer or not

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);	// Create a window - name, size/coordinates, extra attributes
	m_glContext = SDL_GL_CreateContext(m_window);	// NOT SURE, PROBS SOMETHING TO DO WITH MARKING IT AS THE MAIN WINDOW!!!!!!!!!!!

	GLenum status = glewInit();	// Gathers GL status

	if (status != GLEW_OK)	// Check if GLEW initialized ok
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}
	bisClosed = false;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display()	// Destructor - Destroy context and window
{
	SDL_GL_DeleteContext(m_glContext);	// Remove as main window target
	SDL_DestroyWindow(m_window);	// Delete window
	SDL_Quit();	// NOT SURE!!!!!!!!!!!!!!!!!!!!!!!
}

void Display::Update()	// Update the window
{
	SDL_GL_SwapWindow(m_window);	// Swaps buffers - requires double buffering

	SDL_Event e;	// Gathers SDL events

	while (SDL_PollEvent(&e)) // Loop through all pending events to see if any are "close"
	{
		if (e.type == SDL_QUIT)
		{
			bisClosed = true;
		}
	}
}

bool Display::IsClosed() // Returns "closed" status, used in main loop
{
	return bisClosed;
}

void Display::Clear(float r, float g, float b, float a)	// Sets screen colour
{
	glClearColor(r, g, b, a);	// Sets the colours to be used
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clears old colours and replaces them with the new values in glClearColor
	
}

