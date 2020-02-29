#include "Precompile.h"
#include "Application.h"


#include "log.h"

//#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include "Input.h"

namespace Molers {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	 Application* Application::s_Instance = nullptr;

	Application::Application()
	{	
		MOLERS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispathcer(e);//事件调度程序
		dispathcer.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));


		MOLERS_CORE_TRACE("{0}", e);
		//应用结束时删除图层？
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}


	}

	//应用增加图层
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	//应用增加图叠加图层
	void Application::PushOverLayer(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	
	void Application::Run()
	{
		//WindowResizeEvent e(1080, 720);
		//
		//if (e.IsInCategory(EventCategoryApplication))
		//{
		//	MOLERS_TRACE(e);
		//}
		//if (e.IsInCategory(EventCategoryInput))
		//{
		//	MOLERS_TRACE(e);
		//}
		//MOLERS_TRACE(e);  log::GetClientLogger()->trace(e);

		while (true)//每帧循环
		{
			while (m_Running)
			{	
				glClearColor(1, 0, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);

				//图层更新 循环
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();

				//auto [x, y] = Input::GetMousePosition();
				//
				//MOLERS_CORE_TRACE("{0},{1}", x, y);

				m_Window->OnUpdate();

				

			}
		}
	}

	//关闭窗口
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;//在Application::Run的判断中m_Running为0 关闭窗口 不再更新
		return true;
	}

}