#pragma once

//Libraries
#include <GLM/glm.hpp>
//Inbuilt
#include <vector>
//SourceCode


//Vertex data representation
	struct Vertex 
	{
		glm::vec3 pos; // Vertex position (x, y, z)
		glm::vec3 col; // Vertex colour (r, g, b)
	};