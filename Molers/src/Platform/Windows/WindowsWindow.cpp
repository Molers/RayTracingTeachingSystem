#include "Precompile.h"
#include "WindowsWindow.h"

#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/ApplicationEvents.h"

#include "glad/glad.h"
//#include "GLFW/glfw3.h"

namespace Molers {

	//static uint8_t s_GLFWWindowCount = 0;
	//
	//错误回调
	static void GLFWErrorCallback(int error, const char* description)
	{
		MOLERS_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	static bool s_GLFWInitialized = false;
	//创建窗口
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		//HZ_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		//HZ_PROFILE_FUNCTION();

		Shutdown();
	}
	//初始化窗口
	void WindowsWindow::Init(const WindowProps& props)
	{
		//HZ_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		MOLERS_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		

		if (!s_GLFWInitialized)
			//if (s_GLFWWindowCount == 0)
		{
			//MOLERS_PROFILE_SCOPE("glfwInit");
			int success = glfwInit();
			MOLERS_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		//		{
		//			HZ_PROFILE_SCOPE("glfwCreateWindow");
		//#if defined(HZ_DEBUG)
		//			if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
		//				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		//#endif
		//			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		//			++s_GLFWWindowCount;
		//		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		//m_Context = GraphicsContext::Create(m_Window);
		//m_Context->Init();

		glfwMakeContextCurrent(m_Window);

		//glad初始化 在上下文创建后
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MOLERS_CORE_ASSERT(status, "failed to initalize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// GLFW callback 回调函数 一些窗口Window,键盘key,鼠标Mouse的回调函数 调用Events里的函数
		
			//窗口重新设置大小回调
			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);


			});

			//窗口关闭回调
			glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});
			//键盘
			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{//按下
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}//释放 抬起
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}//重复按下次数
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}

				}

			});

			//
			glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);

			});


			//鼠标按下抬起
			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{//按下
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}//释放 抬起
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});
			//鼠标滚动
			glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);

				data.EventCallback(event);


			});
			//光标位置
			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

		

	}
		// Set GLFW callbacks
//		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
//		{
//			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
//			data.Width = width;
//			data.Height = height;
//
//			WindowResizeEvent event(width, height);
//			data.EventCallback(event);
//		});
//
//		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
//		{
//			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
//			WindowCloseEvent event;
//			data.EventCallback(event);
//		});
//
//		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
//		{
//			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
//
//			switch (action)
//			{
//			case GLFW_PRESS:
//			{
//				KeyPressedEvent event(static_cast<KeyCode>(key), 0);
//				data.EventCallback(event);
//				break;
//			}
//			case GLFW_RELEASE:
//			{
//				KeyReleasedEvent event(static_cast<KeyCode>(key));
//				data.EventCallback(event);
//				break;
//			}
//			case GLFW_REPEAT:
//			{
//				KeyPressedEvent event(static_cast<KeyCode>(key), 1);
//				data.EventCallback(event);
//				break;
//			}
//			}
//		});
//
		
//
//		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
//		{
//			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
//
//			switch (action)
//			{
//			case GLFW_PRESS:
//			{
//				MouseButtonPressedEvent event(static_cast<MouseCode>(button));
//				data.EventCallback(event);
//				break;
//			}
//			case GLFW_RELEASE:
//			{
//				MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
//				data.EventCallback(event);
//				break;
//			}
//			}
//		});
//
//		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
//		{
//			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
//
//			MouseScrolledEvent event((float)xOffset, (float)yOffset);
//			data.EventCallback(event);
//		});
//
//		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
//		{
//			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
//
//			MouseMovedEvent event((float)xPos, (float)yPos);
//			data.EventCallback(event);
//		});
//	}

	void WindowsWindow::Shutdown()
	{
		//HZ_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		//--s_GLFWWindowCount;
		glfwTerminate();
		//if (s_GLFWWindowCount == 0)
		//{
		//	
		//}
	}

	void WindowsWindow::OnUpdate()
	{
		//HZ_PROFILE_FUNCTION();

		glfwPollEvents();
		glfwSwapBuffers(m_Window);

		//m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		//HZ_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}