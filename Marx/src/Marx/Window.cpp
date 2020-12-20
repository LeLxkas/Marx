#include "mxpch.h"

#include "Window.h"
#include "Log.h"
#include "Exceptions/MarxException.h"
#include "Exceptions/ExceptionMacros.h"

#include "Marx/Events/Application.h"
#include "Marx/Events/Keyboard.h"
#include "Marx/Events/Mouse.h"

namespace Marx
{
	static int s_windowCount = 0;
	static bool s_windowClassInitialized = false;

	WNDCLASS Window::WindowManager::m_wc;
	const char* Window::WindowManager::m_name = "Marx WindowClass";
	std::unordered_map<HWND, Window*> Window::WindowManager::m_mapWindows;

	Window* Window::create(const WindowDesc& desc)
	{
		return new Window(desc);
	}

	Window::~Window()
	{
		shutdown();
	}

	void Window::onUpdate()
	{
		WindowManager::handleMessages();
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
				WindowManager::init(),
				"Could not initialize WindowManager"
			);
			s_windowClassInitialized = true;
		}

		MX_VERIFY_THROW_INFO(
			m_hWnd = CreateWindowEx(
				0,
				WindowManager::getName(),
				m_title.c_str(),
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,
				NULL,
				NULL,
				WindowManager::getInstance(),
				this
			),
			"Could not create window!"
		);

		ShowWindow(m_hWnd, SW_SHOW);
		++s_windowCount;
		m_isInitialized = true;
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
			--s_windowCount;
			WindowManager::unregisterWindow(m_hWnd);
			m_isInitialized = false;
		}
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
			WindowCloseEvent event;
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

			WindowResizeEvent event(width, height);
			m_eventCallback(event);
			break;
		}
		// ---------- KEYBOARD MESSAGES ----------
		case WM_KEYDOWN:
		{
			int repeatCount = LOWORD(lParam);
			KeyPressEvent event((int)wParam, repeatCount);
			m_eventCallback(event);
			break;
		}
		case WM_KEYUP:
		{
			KeyReleaseEvent event((int)wParam);
			m_eventCallback(event);
			break;
		}
		// ---------- MOUSE MESSAGES ----------
		case WM_LBUTTONDOWN:
		{
			MouseButtonPressEvent event(MouseButton_Left);
			m_eventCallback(event);
			break;
		}
		case WM_MBUTTONDOWN:
		{
			MouseButtonPressEvent event(MouseButton_Mid);
			m_eventCallback(event);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			MouseButtonPressEvent event(MouseButton_Right);
			m_eventCallback(event);
			break;
		}
		case WM_XBUTTONDOWN:
		{
			int x = HIWORD(wParam);
			MouseButton btn = (x == XBUTTON1) ? MouseButton_X1 : MouseButton_X2;
			MouseButtonPressEvent event(btn);
			m_eventCallback(event);
			break;
		}
		case WM_LBUTTONUP:
		{
			MouseButtonReleaseEvent event(MouseButton_Left);
			m_eventCallback(event);
			break;
		}
		case WM_MBUTTONUP:
		{
			MouseButtonReleaseEvent event(MouseButton_Mid);
			m_eventCallback(event);
			break;
		}
		case WM_RBUTTONUP:
		{
			MouseButtonReleaseEvent event(MouseButton_Right);
			m_eventCallback(event);
			break;
		}
		case WM_XBUTTONUP:
		{
			int x = HIWORD(wParam);
			MouseButton btn = (x == XBUTTON1) ? MouseButton_X1 : MouseButton_X2;
			MouseButtonReleaseEvent event(btn);
			m_eventCallback(event);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			float delta = GET_WHEEL_DELTA_WPARAM(wParam);
			delta /= WHEEL_DELTA;
			MouseScrollEvent event(delta);
			m_eventCallback(event);
			break;
		}
		case WM_MOUSEHWHEEL:
		{
			float delta = GET_WHEEL_DELTA_WPARAM(wParam);
			delta /= WHEEL_DELTA;
			MouseHScrollEvent event(delta);
			m_eventCallback(event);
			break;
		}
		case WM_MOUSEMOVE:
		{
			POINTS p = MAKEPOINTS(lParam);
			MouseMoveEvent event((float)p.x, (float)p.y);
			m_eventCallback(event);
		}
		// ---------- DEFAULT BEHAVIOR ----------
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		return 0;
	}

	bool Window::WindowManager::init()
	{
		m_wc.lpfnWndProc = wndProcForward;
		m_wc.hInstance = getInstance();
		m_wc.lpszClassName = m_name;

		return RegisterClass(&m_wc);
	}

	bool Window::WindowManager::shutdown()
	{
		return UnregisterClass(getName(), getInstance());
	}

	HINSTANCE Window::WindowManager::getInstance()
	{
		return GetModuleHandle(NULL);
	}

	const char* Window::WindowManager::getName()
	{
		return m_name;
	}

	void Window::WindowManager::registerWindow(HWND hWnd, Window* pWnd)
	{
		MX_ASSERT(
			m_mapWindows.find(hWnd) == m_mapWindows.end(),
			"Handle {0} already registered!", reinterpret_cast<uintptr_t>(hWnd)
		);
		m_mapWindows.insert(std::make_pair(hWnd, pWnd));
	}

	void Window::WindowManager::unregisterWindow(HWND hWnd)
	{
		MX_ASSERT(
			m_mapWindows.find(hWnd) != m_mapWindows.end(),
			"Handle not registered!"
		);
		m_mapWindows.erase(hWnd);
	}

	std::optional<int> Window::WindowManager::handleMessages()
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

	LRESULT CALLBACK Window::WindowManager::wndProcForward(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		auto it = m_mapWindows.find(hWnd);
		switch (uMsg)
		{
		case WM_GETMINMAXINFO:
		{
			return 0;
		}
		case WM_NCCREATE:
		{
			auto pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
			auto pWnd = reinterpret_cast<Window*>(pCreateStruct->lpCreateParams);
			registerWindow(hWnd, pWnd);
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		}

		return it->second->wndProc(hWnd, uMsg, wParam, lParam);
	}
}