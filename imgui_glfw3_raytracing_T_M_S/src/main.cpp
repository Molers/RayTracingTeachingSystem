
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/GL.h>

//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"
// settings

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
static void glfw_error_callback(int error, const char* description);




int main(int, char**)
{	



	// Setup window //��ʼ��OpenGl
	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	// Decide GL+GLSL versions ����GL�İ汾��
	//const char* glsl_version = "#version 130";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", glfwGetPrimaryMonitor(), NULL); ����ȫ��

	//If window creation fails, NULL will be returned, so it is necessary to check the return value.
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	

	//  ����������.�Լ����н���.
	glfwMakeContextCurrent(window); //��������� ���������������

	//glfwSetKeyCallback(window, key_callback);//ע���˳��¼�

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //ע��ı��Ӵ���С�ĺ���

	glfwSwapInterval(1); // Enable vsync

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}



//���󱨸�
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
//����¼�
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
//�˳�
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
//�϶��ı��С
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}