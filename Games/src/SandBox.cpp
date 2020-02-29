
#include <MolersEngine.h>
//�� ����
class ExampleLayer : public Molers::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{

	}
	//���� //ÿ֡ѭ��
	void OnUpdate() override
	{
		//MOLERS_INFO("ExampleLayer::Update");
		
		if(Molers::Input::IsKeyPressed(ENGINE_KEY_TAB))
			MOLERS_TRACE("Tab key is pressed!(poll)");

	}
	//����
	void OnEvent(Molers::Event& event) override
	{
		//MOLERS_TRACE("{0}", event);

		if (event.GetEventType() == Molers::EventType::KeyPressed)
		{
			Molers::KeyPressedEvent& e = (Molers::KeyPressedEvent&) event;
			if(e.GetKeyCode()== ENGINE_KEY_TAB)
				MOLERS_TRACE("Tab key is pressed (event)!");

			MOLERS_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class SandBox : public Molers::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new Molers::ImGuiLayer());
	}
	~SandBox()
	{

	}
};

Molers::Application* Molers::CreateApplication()
{
	return new SandBox();//��ʼ��
}