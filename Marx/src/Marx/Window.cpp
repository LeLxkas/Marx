#include "mxpch.h"

#include "Window.h"
#include "Log.h"
#include "Exceptions/MarxException.h"
#include "Exceptions/ExceptionMacros.h"

#include "Marx/Events/MouseEvents.h"
#include "Marx/Events/WindowEvents.h"
#include "Marx/Events/KeyboardEvents.h"

namespace Marx
{

	int Window::s_windowCount = 0;
	WNDCLASS Window::Manager::m_wc;
	const char* Window::Manager::m_name = "Marx WindowClass";
	std::unordered_map<HWND, Window*> Window::Manager::m_mapWindows;

	Window* Window::create(const WindowDesc& desc)
	{
		return new Window(desc);
	}

	Window::~Window()
	{
		shutdown();
	}

	void Window::shutdown()
	{
		if (m_isInitialized)
		{
			MX_CORE_INFO("Destroying window '{0}'", m_title);
			MX_VERIFY_THROW_INFO(
				DestroyWindow(m_hWnd),
				"Could not destroy window!"
			);
			Manager::unregisterWindow(m_hWnd);
			--s_windowCount;
			m_isInitialized = false;
		}
	}

	void Window::onUpdate()
	{
		Manager::handleMessages();
	}

	void Window::init(const WindowDesc& desc)
	{
		m_title = desc.title;
		m_width = desc.width;
		m_height = desc.height;
		m_eventCallback = defaultWindowCallback;

		MX_CORE_INFO("Creating window '{0}' ({1}, {2})", m_title, m_width, m_height);

		if (!s_windowClassInitialized)
		{
			MX_CORE_WARN("WindowManager is not initizalized yet. Initializing it now");
			MX_VERIFY_THROW_INFO(
				Manager::init(),
				"Could not initialize WindowManager"
			);
			s_windowClassInitialized = true;
		}

		MX_VERIFY_THROW_INFO(
			m_hWnd = CreateWindowEx(
				0,
				Manager::getName(),
				m_title.c_str(),
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,
				NULL,
				NULL,
				Manager::getInstance(),
				this
			),
			"Could not create window!"
		);

		ShowWindow(m_hWnd, SW_SHOW);
		++s_windowCount;
		m_isInitialized = true;
	}

	Window::Window(const WindowDesc& desc)
	{
		init(desc);
	}

	LRESULT CALLBACK Window::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		// ---------- WINDOW MESSAGES ----------
		case WM_CLOSE:
		{
			WindowCloseEvent event(this);
			m_eventCallback(event);
			break;
		}
		case WM_DESTROY:
		{
			if (s_windowCount == 1)
			{
				PostQuitMessage(0);
			}
			break;
		}
		case WM_SIZE:
		{
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);

			m_width = width;
			m_height = height;

			WindowResizeEvent event(this, width, height);
			m_eventCallback(event);
			break;
		}
		// ---------- KEYBOARD MESSAGES ----------
		case WM_KEYDOWN:
		{
			int repeatCount = LOWORD(lParam);
			KeyPressEvent event(this, (int)wParam, repeatCount);
			m_eventCallback(event);
			break;
		}
		case WM_KEYUP:
		{
			KeyReleaseEvent event(this, (int)wParam);
			m_eventCallback(event);
			break;
		}
		// ---------- MOUSE MESSAGES ----------
		case WM_LBUTTONDOWN:
		{
			MouseButtonPressEvent event(this, MouseButton_Left);
			m_eventCallback(event);
			break;
		}
		case WM_MBUTTONDOWN:
		{
			MouseButtonPressEvent event(this, MouseButton_Mid);
			m_eventCallback(event);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			MouseButtonPressEvent event(this, MouseButton_Right);
			m_eventCallback(event);
			break;
		}
		case WM_XBUTTONDOWN:
		{
			int x = HIWORD(wParam);
			MouseButton btn = (x == XBUTTON1) ? MouseButton_X1 : MouseButton_X2;
			MouseButtonPressEvent event(this, btn);
			m_eventCallback(event);
			break;
		}
		case WM_LBUTTONUP:
		{
			MouseButtonReleaseEvent event(this, MouseButton_Left);
			m_eventCallback(event);
			break;
		}
		case WM_MBUTTONUP:
		{
			MouseButtonReleaseEvent event(this, MouseButton_Mid);
			m_eventCallback(event);
			break;
		}
		case WM_RBUTTONUP:
		{
			MouseButtonReleaseEvent event(this, MouseButton_Right);
			m_eventCallback(event);
			break;
		}
		case WM_XBUTTONUP:
		{
			int x = HIWORD(wParam);
			MouseButton btn = (x == XBUTTON1) ? MouseButton_X1 : MouseButton_X2;
			MouseButtonReleaseEvent event(this, btn);
			m_eventCallback(event);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			float delta = GET_WHEEL_DELTA_WPARAM(wParam);
			delta /= WHEEL_DELTA;
			MouseScrollEvent event(this, delta);
			m_eventCallback(event);
			break;
		}
		case WM_MOUSEHWHEEL:
		{
			float delta = GET_WHEEL_DELTA_WPARAM(wParam);
			delta /= WHEEL_DELTA;
			MouseHScrollEvent event(this, delta);
			m_eventCallback(event);
			break;
		}
		case WM_MOUSEMOVE:
		{
			POINTS p = MAKEPOINTS(lParam);
			MouseMoveEvent event(this, (float)p.x, (float)p.y);
			m_eventCallback(event);
		}
		// ---------- DEFAULT BEHAVIOR ----------
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		return 0;
	}

	bool Window::Manager::init()
	{
		m_wc.lpfnWndProc = wndProcSetup;
		m_wc.hInstance = getInstance();
		m_wc.lpszClassName = m_name;

		return RegisterClass(&m_wc);
	}

	bool Window::Manager::shutdown()
	{
		return UnregisterClass(getName(), getInstance());
	}

	HINSTANCE Window::Manager::getInstance()
	{
		return GetModuleHandle(NULL);
	}

	const char* Window::Manager::getName()
	{
		return m_name;
	}

	void Window::Manager::registerWindow(HWND hWnd, Window* pWnd)
	{
		MX_ASSERT(
			m_mapWindows.find(hWnd) == m_mapWindows.end(),
			"Handle already registered!"
		);
		m_mapWindows.insert(std::make_pair(hWnd, pWnd));
	}

	void Window::Manager::unregisterWindow(HWND hWnd)
	{
		MX_ASSERT(
			m_mapWindows.find(hWnd) != m_mapWindows.end(),
			"Handle not registered!"
		);
		m_mapWindows.erase(hWnd);
	}

	void Window::Manager::setProcedure(Procedure proc, HWND hWnd)
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

	std::optional<int> Window::Manager::handleMessages()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
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

	LRESULT CALLBACK Window::Manager::wndProcSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_NCCREATE)
		{
			// Get pointer to Window class calling 'CreateWindowEx'
			auto pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
			auto pWnd = reinterpret_cast<Window*>(pCreateStruct->lpCreateParams);
			// Register window
			registerWindow(hWnd, pWnd);
			// Set procedure to default
			setProcedure(Procedure::Default, hWnd);
			return wndProcForward(hWnd, uMsg, wParam, lParam);
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT CALLBACK Window::Manager::wndProcForward(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		auto it = m_mapWindows.find(hWnd);
		return it->second->wndProc(hWnd, uMsg, wParam, lParam);
	}
}