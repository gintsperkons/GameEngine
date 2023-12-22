#pragma once
//Libraries
#include <GLFW/glfw3.h>
//Inbuilt
#include <string>
//SourceCode
#include "../Rendering/Renderer.h"

class Renderer;
class Window
{		
		std::string wId;
		GLFWwindow *window;
		Renderer* renderer;

		void InitWindow(std::string wName, const int width, const int height);
		void InitRenderer();

	protected:
	public:
		void CreateWindow(std::string wId, std::string wName = "Base Window", const int width = 800, const int height = 600);
		bool WindowShouldClose();
		GLFWwindow *GetGLFWWindow();
		void CloseWindow();
		~Window();
		//Getters
		std::string GetID();
		//Setters
		void SetTitle(std::string newTitle);
};

