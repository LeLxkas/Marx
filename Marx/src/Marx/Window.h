#pragma once

#include "mxpch.h"

#include "Marx/Core.h"
#include "Marx/Events/Event.h"

namespace Marx
{
	static bool s_windowClassInitialized = false;

	struct WindowDesc
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowDesc(const std::string& title = "Marx Engine", unsigned int width = 1280, unsigned int height = 720)
			: title(title), width(width), height(height)
		{}
	};


	class MARX_API Window
	{
	public:
		static Window* create(const WindowDesc& desc = WindowDesc());
		~Window();
	public:
		void shutdown();
		void setEventCallback(const EventCallbackFunc& callback) { m_eventCallback = callback; }
	public:
		static void onUpdate();
		unsigned int getWidth() const { return m_width; };
		unsigned int getHeight() const { return m_height; };
		static unsigned int getCount() { return s_windowCount; }
	private:
		void init(const WindowDesc& desc);
	private:
		Window(const WindowDesc& desc);
	private:
		LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static void defaultWindowCallback(Event& e) {}
	private:
		HWND m_hWnd;
		unsigned int m_width;
		unsigned int m_height;
		bool m_isInitialized;
		DISABLE_DLL_INTERFACE_WARN;
		std::string m_title;
		EventCallbackFunc m_eventCallback;
		REENABLE_DLL_INTERFACE_WARN;
	private:
		static int s_windowCount;
	private:
		class Manager
		{
		public:
			enum class Procedure
			{
				Setup,
				Default
			};
		public:
			static bool init();
			static bool shutdown();
			static HINSTANCE getInstance();
			static const char* getName();
			static void registerWindow(HWND hWnd, Window* pWnd);
			static void unregisterWindow(HWND hWnd);
			static void setProcedure(Procedure proc = Procedure::Default, HWND hWnd = nullptr);
		public:
			static std::optional<int> handleMessages();
		private:
			static LRESULT CALLBACK wndProcSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK wndProcForward(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		private:
			static WNDCLASS m_wc;
			static const char* m_name;
		private:
			static std::unordered_map<HWND, Window*> m_mapWindows;
		};
	};

}