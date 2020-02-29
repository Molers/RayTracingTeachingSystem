#pragma once
#include "Core/Layer.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"

namespace Molers
{
	class __declspec(dllexport) ImGuiLayer:public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();//GUI层的事物添加
		void OnDetach();//GUI层的事物删除
		void OnUpdate();//GUI层更新
		void OnEvent(Event& event);//GUI层的事件

	private:

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnwindowResizeEvent(WindowResizeEvent& e);

	private:
		float m_Time = 0.0f;
	};
}


