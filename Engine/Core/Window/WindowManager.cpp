#include "WindowManager.h"
#include <stdexcept>

WindowManager *instance;

WindowManager *WindowManager::GetInstance()
{
    if (instance == nullptr)
		instance = new WindowManager();
    return instance;
}

void WindowManager::DestroyInstance()
{
    if (instance != nullptr)
		delete instance;
}

WindowManager::~WindowManager()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void WindowManager::InitWindow(std::string wName, const int width, const int height)
{
	// Initialise GLFW
	if (!glfwInit())
		throw std::runtime_error("Failed to initialise GLFW");

	// Set GLFW to not work with OpenGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

bool WindowManager::WindowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void WindowManager::PollEvents()
{
	glfwPollEvents();
}

GLFWwindow *WindowManager::GetWindow()
{
	return this->window;
}
