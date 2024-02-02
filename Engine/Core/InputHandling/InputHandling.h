#pragma once

//Libraries
//Inbuilt
//SourceCode
class InputHandling
{   	
    protected:
    char keyStates[1024];
        void static KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        InputHandling();
	public:
    enum KeyStates {
        Released = 0,
        Pressed = 1,
        Held = 2
    };
        void Update();


        
};