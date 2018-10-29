#include "ModuleConsole.h"
#include "Application.h"
#include "imgui.h"

ModuleConsole::ModuleConsole()
{
}


ModuleConsole::~ModuleConsole()
{
}

bool ModuleConsole::drawSubmodule()
{
	if (ImGui::CollapsingHeader("Console"))
	{
		ImGui::TextUnformatted(App->consoleBuffer.begin());

	}
	return true;
}
