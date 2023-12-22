//Libraries
#include <GLFW/glfw3.h>
//Inbuilt
#include <string>
#include <vector>
//SourceCode
#include "WindowManager.h"

//Singleton instance creation storage and destraction
WindowManager *instance;

WindowManager *WindowManager::GetInstance()
{
	if (instance == nullptr)
		instance = new WindowManager();
	return instance;
}

void WindowManager::DestroyInstance()
{
	glfwTerminate();
	if (instance != nullptr)
		delete instance;
}


//<<<Privates

//clears all heap allocations
void WindowManager::Clear()
{
	//destroy all windows classes and clear the map
	for (std::map<std::string, Window *>::iterator it = allWindows.begin(); it != allWindows.end(); ++it)
	{
		delete it->second;
	}
	allWindows.clear();
}

WindowManager::~WindowManager()
{
	Clear();
}

//>>>Privates

//<<<Publics

//creates window and adds it to the map that it will be accessed from by the id so there can be multiple windows
void WindowManager::CreateWindow(std::string wId, std::string wName, const int width, const int height)
{
	Window *newWindow = new Window();
	newWindow->CreateWindow(wId, wName, width, height);
	allWindows.insert(std::pair(wId, newWindow));
}

//polls glfw events
void WindowManager::PollEvents()
{
	glfwPollEvents();
}

bool WindowManager::ShouldClose()
{	
	std::vector<std::string> toDelete;
	bool shouldClose = true;
	for (std::map<std::string, Window *>::iterator it = allWindows.begin(); it != allWindows.end(); ++it)
	{
	
	if (!it->second->WindowShouldClose())
		shouldClose = false;
	else
		toDelete.push_back(it->first);
}
	for (std::string id : toDelete)
	{
		allWindows.find(id)->second->CloseWindow();
		allWindows.erase(id);
	}

	return shouldClose;
}
//>>>Publics

//<<<Checkers


bool WindowManager::HasAtleastOneWindow()
{
		return !allWindows.empty();
}

//>>>Checkers

//<<<Getters

Window *WindowManager::GetWindow(std::string wId)
{
	if (allWindows.find(wId) != allWindows.end())
		return allWindows.find(wId)->second;
	return nullptr;
}

GLFWwindow *WindowManager::GetGLFWWindow(std::string wId)
{
	if (allWindows.find(wId) != allWindows.end())
		return allWindows.find(wId)->second->GetGLFWWindow();
	return nullptr;
}
//>>>Getters
