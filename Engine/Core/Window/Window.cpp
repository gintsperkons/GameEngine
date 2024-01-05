#include "Window.h"
//Libraries
//Inbuilt
#include <stdexcept>
//SourceCode
#include "../Rendering/Vulkan/VulkanRenderer.h"
#include "Window.h"
#include <iostream>


//<<<Privates
void Window::InitWindow(std::string wName, const int width, const int height)
{
	// Initialise GLFW
	if (!glfwInit())
		throw std::runtime_error("Failed to initialise GLFW");

	// Set GLFW to not work with OpenGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}
void Window::InitRenderer()
{
	// Create Vulkan Renderer instance
	renderer = new VulkanRenderer();
	if (renderer->Init(window) == EXIT_FAILURE)
		throw std::runtime_error("Failed to initialise Vulkan Renderer");
		


}
//>>>Privates

//<<<Publics
void Window::CreateWindow(std::string wId, std::string wName, const int width, const int height)
{	
	this->wId = wId;
	InitWindow(wName, width, height);
	InitRenderer();
}

bool Window::WindowShouldClose()
{	
	return glfwWindowShouldClose(window);
}

void Window::Draw()
{
	renderer->Draw();
}

GLFWwindow *Window::GetGLFWWindow()
{
	return nullptr;
}

void Window::CloseWindow()
{
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
//>>>Getters

//<<<Setters
void Window::SetTitle(std::string newTitle)
{
	glfwSetWindowTitle(window, newTitle.c_str());
}
//>>>Setters