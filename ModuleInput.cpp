#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "glew.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	SDL_PumpEvents(); 

	keyboard = SDL_GetKeyboardState(NULL);

	// TODO 1: Make the application properly close when ESC is pressed (do not use exit())
	// TODO 1: Make the application properly close when ESC is pressed (do not use exit())
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				GLint newWidth = event.window.data1;
				GLint newHeight = event.window.data2;
				glViewport(0, 0, newWidth, newHeight);
			}
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				LOG("Esca has been pressed");
				SDL_Quit();
				exit(0);
			}
			break;

			// Homework: Make the application close up when pressing “X” button of the window
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
			break;
		}

	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}