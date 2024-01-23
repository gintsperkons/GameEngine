#pragma once

//Libraries
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <GLM/glm.hpp>
//Inbuilt
#include <stdexcept>
#include <vector>
//SourceCode
#include "Utilities.h"

class Mesh
{
    int vertexCount;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    VkPhysicalDevice physicalDevice;
    VkDevice device;

    void CreateVertexBuffer(std::vector<Vertex> *vertices);

    uint32_t FindMemoryTypeIndex(uint32_t allowedTypes, VkMemoryPropertyFlags properties);

public:
    Mesh();
    Mesh(VkPhysicalDevice newPhysicalDevice,  VkDevice newDevice, std::vector<Vertex> *vertices);

    //Getters
    int GetVertexCount();
    VkBuffer GetVertexBuffer();
    void DestroyVertexBuffer();

    ~Mesh();
};
