#include "ModuleMenu.h"
#include "Application.h"
#include "imgui.h"

ModuleMenu::ModuleMenu()
{
}


ModuleMenu::~ModuleMenu()
{
}

bool ModuleMenu::drawSubmodule()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Help")) {

			if (ImGui::MenuItem("Documentation"))
				ShellExecute(NULL, "open", "https://github.com/solidajenjo/Engine---Master/wiki",
					NULL, NULL, SW_SHOWNORMAL);
			if (ImGui::MenuItem("Download latest"))
				ShellExecute(NULL, "open", "https://github.com/solidajenjo/Engine---Master",
					NULL, NULL, SW_SHOWNORMAL);
			if (ImGui::MenuItem("Report a bug"))
				ShellExecute(NULL, "open", "https://github.com/solidajenjo/Engine---Master/issues",
					NULL, NULL, SW_SHOWNORMAL);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	return true;
}
