#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void InitGLFW();
GLFWwindow* CreateWindow(int width, int height, const char* name);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
	InitGLFW();
	auto window = CreateWindow(WIDTH, HEIGHT, "Triangle");
	if (!window)
	{
		return -1;
	}

	// Initialize GLAD before calling any OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Tells OpenGL how it should map its NDC (-1 to 1) to window coordinates (0, 800) (0, 600)
	// First two params are bottom left, not top left
	glViewport(0, 0, WIDTH, HEIGHT);
	// Callback to reset viewport whenever the window is resized
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	while (!glfwWindowShouldClose(window))
	{
		// double buffering- swap back buffer with front buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// releases GLFW's allocated resources
	glfwTerminate();
}

void InitGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* CreateWindow(int width, int height, const char* name)
{
	auto window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	return window;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
