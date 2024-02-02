//Libraries
#include "GLFW/glfw3.h"
//Inbuilt
#include <iostream>
//SourceCode
#include "InputHandling.h"
#include "../Window/Window.h"


//<<<Protected

void InputHandling::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Window* windowPointer = (Window*)glfwGetWindowUserPointer(window);

    if (action == GLFW_REPEAT && windowPointer->keyStates[key] == KeyStates::Pressed )
        windowPointer->keyStates[key] = KeyStates::Held;

    if (action == GLFW_PRESS && windowPointer->keyStates[key] == KeyStates::Released )
        windowPointer->keyStates[key] = KeyStates::Pressed;

    if (action == GLFW_RELEASE)
        windowPointer->keyStates[key] = KeyStates::Released;

    
}
InputHandling::InputHandling()
{
    keyStates[1024] = {0};
}
//>>>Protected

//<<<Publics


void InputHandling::Update()
{   
    for (size_t i = 0; i < 1024; i++)
    {
        if (keyStates[i] == KeyStates::Pressed)
            keyStates[i] = KeyStates::Held;
        if (keyStates[i] == KeyStates::Released)
            keyStates[i] = KeyStates::Released;
        /* code */
    }
	glfwPollEvents();
}




//>>>Publics
