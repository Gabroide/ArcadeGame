#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
#include "glew.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = NULL;

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG("Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("Application Update --------------");

				/* SDL_GL_CONTEXT */
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); 
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 
				SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); 
				SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); 
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); 
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

				/* glew initialization */
				GLenum err = glewInit();

				/* glew LOGs */
				LOG("Using Glew %s", glewGetString(GLEW_VERSION));
				LOG("Vendor: %s", glGetString(GL_VENDOR));
				LOG("Renderer: %s", glGetString(GL_RENDERER));
				LOG("OpenGL version supported %s", glGetString(GL_VERSION));
				LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();


			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG("Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	delete App;
	LOG("Bye :)\n");
	return main_return;
}