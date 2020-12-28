#include "mxpch.h"
#include "ImGuiLayer.h"

#include "Marx/Application.h"
#include "Marx/Input/KeyCodes.h"
#include "Marx/Platform/DX11/DX11Window.h"
#include "Marx/Platform/DX11/ImGuiDX11Helper.h"
#include "Marx/Platform/Win32/ImGuiWin32Helper.h"

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
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] =  MX_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] =  MX_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] =  MX_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] =  MX_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] =  MX_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] =  MX_KEY_PRIOR;
		io.KeyMap[ImGuiKey_PageDown] =  MX_KEY_NEXT;
		io.KeyMap[ImGuiKey_Home] =  MX_KEY_HOME;
		io.KeyMap[ImGuiKey_End] =  MX_KEY_END;
		io.KeyMap[ImGuiKey_Insert] =  MX_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] =  MX_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] =  MX_KEY_BACK;
		io.KeyMap[ImGuiKey_Space] =  MX_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] =  MX_KEY_RETURN;
		io.KeyMap[ImGuiKey_Escape] = MX_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] =  MX_KEY_RETURN;
		io.KeyMap[ImGuiKey_A] = 'A';
		io.KeyMap[ImGuiKey_C] = 'C';
		io.KeyMap[ImGuiKey_V] = 'V';
		io.KeyMap[ImGuiKey_X] = 'X';
		io.KeyMap[ImGuiKey_Y] = 'Y';
		io.KeyMap[ImGuiKey_Z] = 'Z';

		ImGui_ImplDX11_Init(DX11Window::DX11Manager::getDevice(), DX11Window::DX11Manager::getContext());
		ImGui_ImplWin32_Init(Win32Window::getWnd()->getNativeWindow());
	}

	void ImGuiLayer::onDetach()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::onUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());

		std::chrono::steady_clock::time_point now = m_clock.now();
		io.DeltaTime = (now - m_time).count() / 1000000000.0f;
		m_time = now;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::SetNextWindowSize({ 90, 50 });
		ImGui::Begin("FPS");
		std::string fps = std::to_string(1.0f / io.DeltaTime);
		ImGui::Text("%s", fps.c_str());
		ImGui::End();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<MouseButtonPressEvent>(MX_BIND_EVENT_METHOD(ImGuiLayer::onMouseButtonPressEvent));
		dispatcher.dispatch<MouseButtonReleaseEvent>(MX_BIND_EVENT_METHOD(ImGuiLayer::onMouseButtonReleaseEvent));
		dispatcher.dispatch<MouseMoveEvent>(MX_BIND_EVENT_METHOD(ImGuiLayer::onMouseMoveEvent));
		dispatcher.dispatch<MouseScrollEvent>(MX_BIND_EVENT_METHOD(ImGuiLayer::onMouseScrollEvent));
		dispatcher.dispatch<MouseHScrollEvent>(MX_BIND_EVENT_METHOD(ImGuiLayer::onMouseHScrollEvent));
		dispatcher.dispatch<KeyPressEvent>(MX_BIND_EVENT_METHOD(ImGuiLayer::onKeyPressEvent));
		dispatcher.dispatch<KeyReleaseEvent>(MX_BIND_EVENT_METHOD(ImGuiLayer::onKeyReleaseEvent));
		dispatcher.dispatch<KeyTypeEvent>(MX_BIND_EVENT_METHOD(ImGuiLayer::onKeyTypeEvent));
		dispatcher.dispatch<WindowResizeEvent>(MX_BIND_EVENT_METHOD(ImGuiLayer::onWindowResizeEvent));
	}

	bool ImGuiLayer::onMouseButtonPressEvent(MouseButtonPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getButton() - 1] = true;
		return false;
	}

	bool ImGuiLayer::onMouseButtonReleaseEvent(MouseButtonReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getButton() - 1] = false;
		return false;
	}

	bool ImGuiLayer::onMouseMoveEvent(MouseMoveEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.getX(), e.getY());
		return false;
	}

	bool ImGuiLayer::onMouseScrollEvent(MouseScrollEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.getDelta();
		return false;
	}

	bool ImGuiLayer::onMouseHScrollEvent(MouseHScrollEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.getDelta();
		return false;
	}

	bool ImGuiLayer::onKeyPressEvent(KeyPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[VK_LCONTROL] || io.KeysDown[VK_RCONTROL];
		io.KeyShift = io.KeysDown[VK_LSHIFT] || io.KeysDown[VK_RSHIFT];
		io.KeyAlt = io.KeysDown[VK_MENU];
		io.KeySuper = io.KeysDown[VK_LWIN] || io.KeysDown[VK_RWIN];
		return false;
	}

	bool ImGuiLayer::onKeyReleaseEvent(KeyReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = false;
		return false;
	}

	bool ImGuiLayer::onKeyTypeEvent(KeyTypeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keyCode = e.getKeyCode();
		if (keyCode > 0 && keyCode < 0x10000)
			io.AddInputCharacter((unsigned short)keyCode);
		return false;
	}

	bool ImGuiLayer::onWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.getWidth(), (float)e.getHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		return false;
	}
}