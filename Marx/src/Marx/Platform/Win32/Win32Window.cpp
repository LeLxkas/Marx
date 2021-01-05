#include "mxpch.h"
#include "Win32Window.h"

#include "Marx/Exceptions/MarxException.h"
#include "Marx/Exceptions/ExceptionMacros.h"

#include "Marx/Events/MouseEvents.h"
#include "Marx/Events/WindowEvents.h"
#include "Marx/Events/KeyboardEvents.h"
#include "Marx/Input/MouseCodes.h"

#include "backends/imgui_impl_win32.h"

#include "Marx/Platform/D3D11/D3D11GraphicsContext.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Marx
{
	Window* Window::create(const WindowDesc& desc)
	{
		return new Win32Window(desc);
	}

	Win32Window::Win32Window(const WindowDesc& desc)
	{
		init(desc);
	}

	Win32Window::~Win32Window()
	{
		shutdown();
	}

	void Win32Window::onUpdate()
	{
		m_pContext->swapBuffers();

		//Win32Manager::handleMessages(m_hWnd);
		Win32Manager::handleMessages(NULL);
	}

	void Win32Window::init(const WindowDesc& desc)
	{
		MX_CORE_ASSERT(!m_initialized, "Win32Window already initialized!");

		RECT r;
		r.top = 0;
		r.left = 0;
		r.bottom = desc.height;
		r.right = desc.width;

		DWORD windowStyle = WS_OVERLAPPEDWINDOW;
		MX_CORE_ASSERT(
			AdjustWindowRect(
				&r,
				windowStyle,
				FALSE
			),
			"Unable to adjust window size!"
		);

		m_title = desc.title;
		m_width = r.right - r.left;
		m_height = r.bottom - r.top;


		MX_CORE_INFO("Creating window '{0}' ({1}, {2})", m_title, m_width, m_height);

		Win32Manager::init();

		MX_VERIFY_THROW_INFO(
			m_hWnd = CreateWindowEx(
				0,
				Win32Manager::getName(),
				m_title.c_str(),
				windowStyle,
				CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,
				NULL,
				NULL,
				Win32Manager::getInstance(),
				this
			),
			"Could not create window!"
		);

		m_pContext = new D3D11GraphicsContext(m_hWnd);
		m_pContext->init();

		ShowWindow(m_hWnd, SW_SHOW);
		m_initialized = true;
	}

	void Win32Window::shutdown()
	{
		if (!m_initialized)
			return;

		m_pContext->shutdown();
		delete m_pContext;

		MX_CORE_INFO("Destroying window '{0}'", m_title);
		MX_VERIFY_THROW_INFO(
			DestroyWindow(m_hWnd),
			"Could not destroy window!"
		);
		Win32Manager::unregisterWindow(m_hWnd);
		Win32Manager::shutdown();
		m_initialized = false;
	}

	LRESULT Win32Window::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		ImGuiIO* pIO = ImGui::GetCurrentContext() ? &ImGui::GetIO() : nullptr;

		switch (uMsg)
		{
			// ---------- WINDOW MESSAGES ----------
		case WM_CLOSE:
		{
			WindowCloseEvent event(this);
			m_eventCallback(event);
			return 0;
		}
		case WM_DESTROY:
		{
			if (getWndCount() == 1)
			{
				PostQuitMessage(0);
			}
			return 0;
		}
		case WM_SIZE:
		{
			if (wParam != SIZE_MINIMIZED)
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);

				m_width = width;
				m_height = height;

				m_pContext->onResize(width, height);

				WindowResizeEvent event(this, width, height);
				m_eventCallback(event);
			}
			return 0;
		}
		case WM_SETFOCUS:
		{
			WindowFocusEvent event(this);
			m_eventCallback(event);
			return 0;
		}
		case WM_KILLFOCUS:
		{
			WindowFocusLossEvent event(this);
			m_eventCallback(event);
			return 0;
		}
		}

		if (!pIO || !pIO->WantCaptureKeyboard)
		{
			switch (uMsg)
			{
				// ----------KEYBOARD MESSAGES----------
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			{
				int isRepeat = (lParam >> 30) & 1;
				KeyPressEvent event(this, (int)wParam, isRepeat);
				m_eventCallback(event);
				return 0;
			}
			case WM_KEYUP:
			case WM_SYSKEYUP:
			{
				KeyReleaseEvent event(this, (int)wParam);
				m_eventCallback(event);
				return 0;
			}
			case WM_CHAR:
			{
				KeyTypeEvent event(this, (int)wParam);
				m_eventCallback(event);
				return 0;
			}
			}
		}

		if (!pIO || !pIO->WantCaptureMouse)
		{
			switch (uMsg)
			{
				// ---------- MOUSE MESSAGES ----------
			case WM_LBUTTONDOWN:
			{
				MouseButtonPressEvent event(this, MX_MOUSE_BUTTON_LEFT);
				m_eventCallback(event);
				return 0;
			}
			case WM_MBUTTONDOWN:
			{
				MouseButtonPressEvent event(this, MX_MOUSE_BUTTON_MID);
				m_eventCallback(event);
				return 0;
			}
			case WM_RBUTTONDOWN:
			{
				MouseButtonPressEvent event(this, MX_MOUSE_BUTTON_RIGHT);
				m_eventCallback(event);
				return 0;
			}
			case WM_XBUTTONDOWN:
			{
				int x = HIWORD(wParam);
				int btn = (x == XBUTTON1) ? MX_MOUSE_BUTTON_X1 : MX_MOUSE_BUTTON_X2;
				MouseButtonPressEvent event(this, btn);
				m_eventCallback(event);
				return 0;
			}
			case WM_LBUTTONUP:
			{
				MouseButtonReleaseEvent event(this, MX_MOUSE_BUTTON_LEFT);
				m_eventCallback(event);
				return 0;
			}
			case WM_MBUTTONUP:
			{
				MouseButtonReleaseEvent event(this, MX_MOUSE_BUTTON_MID);
				m_eventCallback(event);
				return 0;
			}
			case WM_RBUTTONUP:
			{
				MouseButtonReleaseEvent event(this, MX_MOUSE_BUTTON_RIGHT);
				m_eventCallback(event);
				return 0;
			}
			case WM_XBUTTONUP:
			{
				int x = HIWORD(wParam);
				int btn = (x == XBUTTON1) ? MX_MOUSE_BUTTON_X1 : MX_MOUSE_BUTTON_X2;
				MouseButtonReleaseEvent event(this, btn);
				m_eventCallback(event);
				return 0;
			}
			case WM_MOUSEWHEEL:
			{
				float delta = GET_WHEEL_DELTA_WPARAM(wParam);
				delta /= WHEEL_DELTA;
				MouseScrollEvent event(this, delta);
				m_eventCallback(event);
				return 0;
			}
			case WM_MOUSEHWHEEL:
			{
				float delta = GET_WHEEL_DELTA_WPARAM(wParam);
				delta /= WHEEL_DELTA;
				MouseHScrollEvent event(this, delta);
				m_eventCallback(event);
				return 0;
			}
			case WM_MOUSEMOVE:
			{
				POINTS p = MAKEPOINTS(lParam);
				MouseMoveEvent event(this, (float)p.x, (float)p.y);
				m_eventCallback(event);
				return 0;
			}
			}
		}
			
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void Win32Window::Win32Manager::init()
	{
		MX_CORE_WARN("Win32Manager is not initizalized yet. Initializing it now");

		m_wc.lpfnWndProc = wndProcSetup;
		m_wc.hInstance = getInstance();
		m_wc.lpszClassName = m_name;

		RegisterClass(&m_wc);
	}

	void Win32Window::Win32Manager::shutdown()
	{
		if (m_mapWindows.size() > 0)
			return;

		MX_CORE_INFO("Shutting down Win32Manager");

		UnregisterClass(getName(), getInstance());
	}

	void Win32Window::Win32Manager::registerWindow(HWND hWnd, Win32Window* pWnd)
	{
		MX_CORE_ASSERT(
			m_mapWindows.find(hWnd) == m_mapWindows.end(),
			"Handle already registered!"
		);
		m_mapWindows.insert(std::make_pair(hWnd, pWnd));
	}

	void Win32Window::Win32Manager::unregisterWindow(HWND hWnd)
	{
		MX_CORE_ASSERT(
			m_mapWindows.find(hWnd) != m_mapWindows.end(),
			"Handle not registered!"
		);
		m_mapWindows.erase(hWnd);
	}

	void Win32Window::Win32Manager::setProcedure(Procedure proc, HWND hWnd)
	{
		if (!hWnd)
		{
			// Retrieve any active hWnd
			hWnd = FindWindowEx(NULL, NULL, getName(), NULL);
		}
		WNDPROC procedure;
		switch (proc)
		{
		case Procedure::Setup: procedure = wndProcSetup; break;
		case Procedure::Default: procedure = wndProcForward; break;
		}
		if (hWnd)
		{
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)procedure);
		}
	}

	Win32Window* Win32Window::Win32Manager::getWnd(unsigned int index)
	{
		auto& it = m_mapWindows.begin();
		while (index >= 1)
		{
			--index; ++it;
		}
		return it->second;
	}

	std::optional<int> Win32Window::Win32Manager::handleMessages(HWND hWnd)
	{
		MSG msg;
		while (PeekMessage(&msg, hWnd, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return std::optional<int>(static_cast<int>(msg.wParam));
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return std::optional<int>();
	}

	LRESULT CALLBACK Win32Window::Win32Manager::wndProcSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_NCCREATE)
		{
			// Get pointer to Window class calling 'CreateWindowEx'
			auto pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
			auto pWnd = reinterpret_cast<Win32Window*>(pCreateStruct->lpCreateParams);
			// Register window
			registerWindow(hWnd, pWnd);
			// Set procedure to default
			setProcedure(Procedure::Default, hWnd);
			return wndProcForward(hWnd, uMsg, wParam, lParam);
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT CALLBACK Win32Window::Win32Manager::wndProcForward(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		auto it = m_mapWindows.find(hWnd);
		if (it != m_mapWindows.end())
			return it->second->wndProc(hWnd, uMsg, wParam, lParam);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
