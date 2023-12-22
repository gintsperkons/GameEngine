#pragma once
//Libraries
//Inbuilt
//SourceCode
#include "Engine/Core/Window/WindowManager.h"

class WindowManager;

class Engine
{	
	void DestroyElementInstances();
	~Engine();
	protected:
	public:
		
		void Init();
		void Update();
		bool ShouldStop();


		//Singleton instance creation and destraction
		static Engine *GetInstance();
		static void DestroyInstance();
};

