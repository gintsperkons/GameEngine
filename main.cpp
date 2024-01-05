
//Libraries
#define GLFW_INCLUDE_VULKAN

//Inbuilt
#include <stdexcept>
#include <vector>
#include <iostream>

//SourceCode
#include "../GameEngine/Engine.h"



int main()
{
	Engine::GetInstance()->Init();
	WindowManager::GetInstance()->GetWindow("main")->SetTitle("Voxel Game");



	std::cout << "Hello World" << std::endl;

	//Main loop until window is closed
	while (!Engine::GetInstance()->ShouldStop())
	{
		Engine::GetInstance()->Update();
		Engine::GetInstance()->Draw();
	}
	return 0;
}