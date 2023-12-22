#pragma once
//Libraries
#include <GLFW/glfw3.h>
//Inbuilt
#include <string>
#include <map>

//SourceCode
#include "Window.h"

class Window;

class WindowManager
{
	//Windows variables
	std::map<std::string,Window*> allWindows;

	
	void Clear();
	~WindowManager();
	protected:
	public:
		//Creation
		void CreateWindow(std::string wId, std::string wName = "Base Window", const int width = 800, const int height = 600);
		
		void PollEvents();
		bool ShouldClose();


		//Checkers
		bool HasAtleastOneWindow();

		//Getters
		Window *GetWindow(std::string wId);
		GLFWwindow *GetGLFWWindow(std::string wId);

		//Singleton instance creation and destraction
		static WindowManager* GetInstance();
		static void DestroyInstance();
};


//class WindowManager
//{
//	//Windows variables
//	GLFWwindow* window;
//	~WindowManager();
//
//public:
//	void InitWindow(std::string wName = "Base Window", const int width = 800, const int height = 600);
//
//
//	bool WindowShouldClose();
//	void PollEvents();
//
//
//	GLFWwindow *GetWindow();
//
//
//	static WindowManager* GetInstance();
//	static void DestroyInstance();
//};

