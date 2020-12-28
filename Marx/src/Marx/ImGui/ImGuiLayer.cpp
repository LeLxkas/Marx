#include "mxpch.h"
#include "ImGuiLayer.h"

#include "Marx/Application.h"
#include "Marx/Input/KeyCodes.h"
#include "Marx/Platform/DX11/DX11Window.h"

#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"

namespace Marx
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer"), m_time(m_clock.now())
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::onAttach()
	{
		// Setup Dear ImGui context
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplDX11_Init(DX11Window::DX11Manager::getDevice(), DX11Window::DX11Manager::getContext());
		ImGui_ImplWin32_Init(Win32Window::getWnd()->getNativeWindow());

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(Win32Window::getWnd()->getNativeWindow());
		ImGui_ImplDX11_Init(DX11Window::DX11Manager::getDevice(), DX11Window::DX11Manager::getContext());
	}

	void ImGuiLayer::onDetach()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::onImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
}