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
		EventDispatcher dispathcer(e);//�¼����ȳ���
		dispathcer.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));


		MOLERS_CORE_TRACE("{0}", e);
		//Ӧ�ý���ʱɾ��ͼ�㣿
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}


	}

	//Ӧ������ͼ��
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	//Ӧ������ͼ����ͼ��
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

		while (true)//ÿ֡ѭ��
		{
			while (m_Running)
			{	
				glClearColor(1, 0, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);

				//ͼ����� ѭ��
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();

				//auto [x, y] = Input::GetMousePosition();
				//
				//MOLERS_CORE_TRACE("{0},{1}", x, y);

				m_Window->OnUpdate();

				

			}
		}
	}

	//�رմ���
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;//��Application::Run���ж���m_RunningΪ0 �رմ��� ���ٸ���
		return true;
	}

}