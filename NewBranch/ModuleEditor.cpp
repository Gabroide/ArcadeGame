#include "imgui.h"
#include "imgui/exemples/imgui_impl_sdl.h"
#include "imgui/exemples/imgui_impl_opengl3.h"
#include "GL/glew.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleGeneralEditor.h"
#include "ModuleMenu.h"
#include "ModuleFPS.h"
#include "ModuleConsole.h"
#include "SDL.h"





ModuleEditor::ModuleEditor()
{

}


ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	App->imGuiStarted = true;
	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic(); COMMENT
	subModules.push_back(new ModuleMenu());
	subModules.push_back(new ModuleFPS());
	subModules.push_back(new ModuleConsole());
	return true;
}

update_status ModuleEditor::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();
	ImGui::Begin("Editor");
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{

	for (std::list<ModuleGeneralEditor*>::iterator it = subModules.begin(); it != subModules.end(); ++it)
	{
		(*it)->drawSubmodule();
	}
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	for (std::list<SubModuleEditor*>::iterator it = subModules.begin(); it != subModules.end(); ++it)
	{
		delete *it;
	}
	return true;
}
