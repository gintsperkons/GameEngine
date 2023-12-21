#pragma once
//Libraries
#include <GLFW/glfw3.h>
//Inbuilt
#include <string>


class WindowManager
{
	GLFWwindow* window;


	~WindowManager();
public:
	void InitWindow(std::string wName = "Base Window", const int width = 800, const int height = 600);


	bool WindowShouldClose();
	void PollEvents();


	GLFWwindow *GetWindow();


	static WindowManager* GetInstance();
	static void DestroyInstance();
};

