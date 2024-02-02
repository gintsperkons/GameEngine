#include "Window.h"
// Libraries
// Inbuilt
#include <stdexcept>
// SourceCode
#include "../Rendering/Vulkan/VulkanRenderer.h"
#include "../Rendering/OpenGL/OpenGLRenderer.h"
#include "Window.h"
#include <iostream>

//<<<Privates
void Window::InitWindow(std::string wName, const int width, const int height)
{
	// Initialise GLFW
	if (!glfwInit())
		throw std::runtime_error("Failed to initialise GLFW");

	// Set window hints
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	if (rendererType == Renderer::RendererType::Vulkan)
	{
		// Set GLFW to not work with OpenGL
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}
	else if (rendererType == Renderer::RendererType::OpenGL)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
	if (window == NULL)
    {
		throw std::runtime_error("Failed to create GLFW window");
        glfwTerminate();
    }
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	// Set key callback
	glfwSetKeyCallback(window, InputHandling::KeyCallback);

}
void Window::InitRenderer()
{
	// Create Renderer instance
	if (rendererType == Renderer::RendererType::Vulkan)
	{
		Renderer* tempRenderer = new VulkanRenderer();
		if (tempRenderer->Init(window) == EXIT_FAILURE)
			throw std::runtime_error("Failed to initialise Vulkan Renderer");
		renderer = tempRenderer;
	}
	else if (rendererType == Renderer::RendererType::OpenGL)
	{
		Renderer* tempRenderer = new OpenGLRenderer();
		if (tempRenderer->Init(window) == EXIT_FAILURE)
			throw std::runtime_error("Failed to initialise OpenGL Renderer");
		renderer = tempRenderer;
	}
}
//>>>Privates

//<<<Publics
void Window::CreateWindow(std::string wId, std::string wName, const int width, const int height)
{
	this->wId = wId;

	// Set renderer data and type
	rendererType = Renderer::RendererType::Vulkan;
	clearColor = glm::vec4(0.4f, 0.4f, 1.0f, 1.0f);

	InitWindow(wName, width, height);
	InitRenderer();
	glfwShowWindow(window);
}

bool Window::WindowShouldClose()
{
	if (keyStates[GLFW_KEY_ESCAPE] == KeyStates::Pressed || keyStates[GLFW_KEY_ESCAPE] == KeyStates::Held)
		glfwSetWindowShouldClose(window, true);
	return glfwWindowShouldClose(window);
}

void Window::Draw()
{
	renderer->Draw();
}

void Window::PollEvents()
{
	InputHandling::Update();
}

void Window::ChangeRenderer(int newRendererType)
{	
	Renderer* oldRenderer = renderer;
	rendererType = newRendererType;
	InitRenderer();
	delete oldRenderer;
}

GLFWwindow *Window::GetGLFWWindow()
{
	return window;
}

void Window::CloseWindow()
{
	delete renderer;
	glfwDestroyWindow(window);
}

Window::~Window()
{
	CloseWindow();
}
//>>>Publics

//<<<Getters
std::string Window::GetID()
{
	return wId;
}
glm::vec4 Window::GetClearColor()
{
    return clearColor;
}
char Window::GetKeyState(int key)
{
	return keyStates[key];
}
//>>>Getters

//<<<Setters
void Window::SetTitle(std::string newTitle)
{
	glfwSetWindowTitle(window, newTitle.c_str());
}
//>>>Setters