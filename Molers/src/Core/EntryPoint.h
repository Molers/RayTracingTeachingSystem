#pragma once
#ifdef MOLERS_PLATFORM_WINDOWS

//�������ߺ����Ķ����ڱ���ļ���

//��һ��Դ�ļ�������������һ��Դ�ļ����Ѿ�������ⲿ������
//ͬ��ֻ�������ñ������ļ����� extern �ؼ��ּ�����������

extern Molers::Application* Molers::CreateApplication();

int main(int argc ,char ** argv)
{
	//SandBox* sandbox = new SandBox();
	//
	//sandbox->Run();
	//
	//delete sandbox;
	
	//printf("llll");

	//--------Log Test ��־����
	Molers::log::Init();
	Molers::log::GetCoreLogger()->warn("Initialized Log!");
	Molers::log::GetClientLogger()->info("Hello!");

	int a = 5;
	MOLERS_CORE_WARN("Initialized Log!");
	MOLERS_INFO("Hello! Var={0}",a);
	//----------------------------------------------------

	//----------Events����



	//--



	auto app =  Molers::CreateApplication();
	
	app->Run();
	
	delete app;

}


#endif
