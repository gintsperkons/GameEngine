#pragma once
//Libraries
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
//Inbuilt
#include <string>
//SourceCode
#include "../Rendering/Renderer.h"
#include "../InputHandling/InputHandling.h"

class InputHandling;
class Renderer;
class Window : public InputHandling
{	

		int rendererType;
		std::string wId;
		GLFWwindow *window;
		Renderer* renderer;
		glm::vec4 clearColor;

		void InitWindow(std::string wName, const int width, const int height);
		void InitRenderer();

	protected:
	public:
		void CreateWindow(std::string wId, std::string wName = "Base Window", const int width = 800, const int height = 600);
		bool WindowShouldClose();
		void Draw();
		void PollEvents();
		GLFWwindow *GetGLFWWindow();
		void ChangeRenderer(int newRendererType);
		void CloseWindow();
		~Window();
		//Getters
		std::string GetID();
		glm::vec4 GetClearColor();
		char GetKeyState(int key);
		//Setters
		void SetTitle(std::string newTitle);
};

