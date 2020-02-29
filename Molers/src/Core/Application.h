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

			void OnEvent(Event& e);//事件层
			//增加图层 叠加图层
			void PushLayer(Layer* layer);
			void PushOverLayer(Layer* layer);

			//返回窗口
			inline Window& GetWindow() { return *m_Window; }
			//返回应用
			inline static Application& GetApplication() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;//窗口正在运行标志

		LayerStack m_LayerStack;//图层容器

	private:
		static Application* s_Instance;//应用实例
	};

	 Application* CreateApplication();
}
