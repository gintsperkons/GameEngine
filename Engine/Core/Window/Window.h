#pragma once
//Libraries
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
//Inbuilt
#include <string>
//SourceCode
#include "../Rendering/Renderer.h"

class Renderer;
class Window
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
		GLFWwindow *GetGLFWWindow();
		void CloseWindow();
		~Window();
		//Getters
		std::string GetID();
		glm::vec4 GetClearColor();
		//Setters
		void SetTitle(std::string newTitle);
};

