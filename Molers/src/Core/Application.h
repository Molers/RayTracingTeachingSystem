#pragma once

#include "Core.h"

#include "Events/Events.h"
#include "Events/ApplicationEvents.h"

#include "Core/LayerStack.h"

#include "Window.h"


namespace Molers
{
	 class MOLERS_API Application
	{
		public:
			Application();
			virtual ~Application();


			void Run();

			void OnEvent(Event& e);//�¼���
			//����ͼ�� ����ͼ��
			void PushLayer(Layer* layer);
			void PushOverLayer(Layer* layer);

			//���ش���
			inline Window& GetWindow() { return *m_Window; }
			//����Ӧ��
			inline static Application& GetApplication() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;//�����������б�־

		LayerStack m_LayerStack;//ͼ������

	private:
		static Application* s_Instance;//Ӧ��ʵ��
	};

	 Application* CreateApplication();
}
