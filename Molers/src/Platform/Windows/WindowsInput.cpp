#include "Precompile.h"
#include "WindowsInput.h"


#include "Core/Application.h"
#include "GLFW/glfw3.h"

namespace Molers {

	Input* Input::s_Instance = new WindowsInput();

	//键盘是否点击
	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{	
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;

	}
	//鼠标是否点击
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	//获得鼠标X坐标
	float WindowsInput::GetMouseXImpl()
	{	
		//auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		//double xpos, ypos;
		//glfwGetCursorPos(window, &xpos, &ypos);
		//
		//return (float)xpos;

		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	//获得鼠标Y坐标
	float WindowsInput::GetMouseYImpl()
	{
		//auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		//double xpos, ypos;
		//glfwGetCursorPos(window, &xpos, &ypos);
		//
		//return (float)ypos;
		auto [x, y] = GetMousePositionImpl();
		return y;

	}

	


}