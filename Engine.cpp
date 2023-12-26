//Libraries
//Inbuilt
//SourceCode
#include "Engine.h"

//Singleton instance creation storage and destraction
Engine *Engine::instance;

Engine *Engine::GetInstance()
{
	if (instance == nullptr)
		instance = new Engine();
	return instance;
}

void Engine::DestroyInstance()
{
	if (instance != nullptr)
		delete instance;
}


//<<<Privates

void Engine::DestroyElementInstances()
{
	WindowManager::DestroyInstance();
}

Engine::~Engine()
{
	DestroyElementInstances();
}

//>>>Privates


//<<<Publics

void Engine::Init()
{
	// Create window if no window found created before
	if (!WindowManager::GetInstance()->HasAtleastOneWindow())
		WindowManager::GetInstance()->CreateWindow("main", "Engine Window", 1080, 720);
}

//updates the engine
void Engine::Update()
{	
	WindowManager::GetInstance()->PollEvents();
}
bool Engine::ShouldStop()
{
	return WindowManager::GetInstance()->ShouldClose();
}
//>>>Publics
