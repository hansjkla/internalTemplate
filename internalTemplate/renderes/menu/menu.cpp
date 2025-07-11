#include "menu.h"


bool menu::isMenuSetup = false;
bool menu::menuOpen = true;
bool menu::showDemoWindow = true;


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);


LRESULT CALLBACK WindowsProcess(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		menu::menuOpen = !menu::menuOpen;

	if (menu::menuOpen && ImGui_ImplWin32_WndProcHandler(
		hWnd,
		msg,
		wParam,
		lParam
	)) return 1L;

	return CallWindowProc(
		menu::originalWindowProcess,
		hWnd,
		msg,
		wParam,
		lParam
	);
}


void menu::SetupMenu()
{
	if (isMenuSetup)
		return;
	
	originalWindowProcess = (WNDPROC)SetWindowLongPtr(
		gameWindow,
		GWLP_WNDPROC,
		reinterpret_cast<LONG_PTR>(WindowsProcess)
	);

	if (Renderer == RendererOptions::OPENGL || Renderer == RendererOptions::DX11) IMGUI_CHECKVERSION();
	
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(gameWindow);
	
	switch (Renderer)
	{
	case RendererOptions::NONE:
		return;

	case RendererOptions::DX9:
		ImGui_ImplDX9_Init(hooks::realDevice);
		break;

	case RendererOptions::DX10:
		return;

	case RendererOptions::DX11:
		ImGui_ImplDX11_Init(Dx11Hook::device, Dx11Hook::devcon);
		break;

	case RendererOptions::DX12:
		return;

	case RendererOptions::OPENGL:
		ImGui_ImplOpenGL3_Init();
		break;

	case RendererOptions::VULKAN:
		return;

	default:
		break;
	}
		
	isMenuSetup = true;
}


void menu::Render()
{
	if (!isMenuSetup || !menuOpen) return;

	switch (Renderer)
	{
	case RendererOptions::NONE:
		return;

	case RendererOptions::DX9:
		ImGui_ImplDX9_NewFrame();
		break;

	case RendererOptions::DX10:

	case RendererOptions::DX11:
		ImGui_ImplDX11_NewFrame();
		break;

	case RendererOptions::DX12:

	case RendererOptions::OPENGL:
		ImGui_ImplOpenGL3_NewFrame();
		break;

	case RendererOptions::VULKAN:

	default:
		break;
	}
	
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	//ImGui::ShowDemoWindow(&showDemoWindow);
	ImGui::Begin("cool", &showDemoWindow);
	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	
	switch (Renderer)
	{
	case RendererOptions::NONE:

	case RendererOptions::DX9:
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		break;

	case RendererOptions::DX10:

	case RendererOptions::DX11:
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		break;

	case RendererOptions::DX12:

	case RendererOptions::OPENGL:
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		break;

	case RendererOptions::VULKAN:

	default:
		break;
	}
	return;
}


void menu::Destroy()
{
	switch (Renderer)
	{
	case RendererOptions::NONE:
		return;

	case RendererOptions::DX9:
		ImGui_ImplDX9_Shutdown();
		break;

	case RendererOptions::DX10:

	case RendererOptions::DX11:
		ImGui_ImplDX11_Shutdown();
		break;

	case RendererOptions::DX12:

	case RendererOptions::OPENGL:
		ImGui_ImplOpenGL3_Shutdown();
		break;

	case RendererOptions::VULKAN:

	default:
		break;
	}
	
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtr(
		gameWindow,
		GWLP_WNDPROC,
		reinterpret_cast<LONG_PTR>(originalWindowProcess)
	);
}
