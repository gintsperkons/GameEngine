#pragma once
//Libraries
#include <GLFW/glfw3.h>
//Inbuilt
//SourceCode

class Renderer
{
	protected:
	public:
		virtual int Init(GLFWwindow* window) = 0;
		virtual void Draw() = 0;
		virtual void Update() = 0;
		virtual void Destroy() = 0;

		~Renderer(){};
		Renderer(){};

		enum RendererType
		{
			Vulkan,
			OpenGL
		};
};