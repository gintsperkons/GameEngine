#pragma once
//Libraries
//Inbuilt
#include <vector>
//SourceCode
#include "../RendererStructures.h"

class GLMesh
{
    void CleanUp();
public:
    unsigned int VAO, VBO, EBO;
    GLMesh();
    GLMesh(std::vector<Vertex> *vertices);
    ~GLMesh();
};


