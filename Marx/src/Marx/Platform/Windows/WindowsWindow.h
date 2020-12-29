#pragma once

#include "Marx/Window.h"

#include "Marx/Renderer/GraphicsContext.h"

namespace Marx
{
	class MARX_API Win32Window : public Window
	{
	public:
		Win32Window(const WindowDesc& desc);
		virtual ~Win32Window();
	public:
		virtual void clear(float r, float g, float b) override;
		virtual void onUpdate() override;
		inline unsigned int getWidth() const override { return m_width; }
		inline unsigned int getHeight() const override { return m_height; }
		static unsigned int getWndCount() { return (unsigned int)Win32Manager::getWndCount(); }
		static Win32Window* getWnd(unsigned int index = 0) { return Win32Manager::getWnd(index); }
		virtual void* getNativeWindow() const override { return m_hWnd; }
	public:
		inline void setEventCallback(const EventCallbackFunc& callback) override { m_eventCallback = callback; }
	protected:
		void init(const WindowDesc& desc);
		virtual void shutdown() override;
	protected:
		LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		unsigned int m_width;
		unsigned int m_height;
		HWND m_hWnd;
		bool m_initialized = false;
		DISABLE_DLL_INTERFACE_WARN;
		std::string m_title;
		EventCallbackFunc m_eventCallback = [](Event&) {};
		REENABLE_DLL_INTERFACE_WARN;
		GraphicsContext* m_pContext;
	private:
		class Win32Manager
		{
		public:
			enum class Procedure
			{
				Setup,
				Default
			};
		public:
			static void init();
			static void shutdown();
			static HINSTANCE getInstance() { return GetModuleHandle(NULL); }
			static const char* getName() { return m_name; }
			static void registerWindow(HWND hWnd, Win32Window* pWnd);
			static void unregisterWindow(HWND hWnd);
			static void setProcedure(Procedure proc = Procedure::Default, HWND hWnd = nullptr);
			static size_t getWndCount() { return m_mapWindows.size(); }
			static Win32Window* getWnd(unsigned int index);
		public:
			static std::optional<int> handleMessages(HWND hWnd);
		private:
			static LRESULT CALLBACK wndProcSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			static LRESULT CALLBACK wndProcForward(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		private:
			inline static WNDCLASS m_wc;
			inline static const char* m_name = "Marx WindowClass";
		private:
			inline static std::unordered_map<HWND, Win32Window*> m_mapWindows;
		};
	};
}