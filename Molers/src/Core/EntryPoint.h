#pragma once
#ifdef MOLERS_PLATFORM_WINDOWS

//变量或者函数的定义在别的文件中

//在一个源文件中想引用另外一个源文件中已经定义的外部变量，
//同样只需在引用变量的文件中用 extern 关键字加以声明即可

extern Molers::Application* Molers::CreateApplication();

int main(int argc ,char ** argv)
{
	//SandBox* sandbox = new SandBox();
	//
	//sandbox->Run();
	//
	//delete sandbox;
	
	//printf("llll");

	//--------Log Test 日志测试
	Molers::log::Init();
	Molers::log::GetCoreLogger()->warn("Initialized Log!");
	Molers::log::GetClientLogger()->info("Hello!");

	int a = 5;
	MOLERS_CORE_WARN("Initialized Log!");
	MOLERS_INFO("Hello! Var={0}",a);
	//----------------------------------------------------

	//----------Events测试



	//--



	auto app =  Molers::CreateApplication();
	
	app->Run();
	
	delete app;

}


#endif
