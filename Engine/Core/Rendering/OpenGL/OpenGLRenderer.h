#pragma once
//Libraries
//Inbuilt
//SourceCode
#include "Mesh.h"
#include "../Renderer.h"

class GLMesh;
class Renderer;
class OpenGLRenderer : public Renderer
{
//Render Setting
glm::vec4 clearColor;

GLMesh firstMesh;
~OpenGLRenderer();
unsigned int shaderProgram;
protected:
public:
	int Init(GLFWwindow *newWindow);
	void Draw();
	void Update();
	void Destroy();
	void CleanUp();
};

