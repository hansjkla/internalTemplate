#include "menu.h"

bool menuGL::setupMenuGL = false;
bool menuGL::showDemoWindow = true;

bool menuGL::SetupImGuiGL()
{
	if (!setupMenuGL)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_InitForOpenGL(glHook::gameWindow);
		ImGui_ImplOpenGL3_Init();

		setupMenuGL = true;
	}
	else return false;
	
	return true;
}

void menuGL::renderDemoWindow()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow(&showDemoWindow);
	

	ImGui::Render();
	ImGui::EndFrame();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void menuGL::Destroy()
{
	if (setupMenuGL)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
}
