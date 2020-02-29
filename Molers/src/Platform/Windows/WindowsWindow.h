
#include "Core/Window.h"
//#include "Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>
//#include "glad/glad.h"
namespace Molers {

	class __declspec(dllexport) WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes 回调函数
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }//返回窗口
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();//关闭
	private:
		GLFWwindow* m_Window;
		//Scope<GraphicsContext> m_Context;

		struct WindowData//窗口的数据
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}


