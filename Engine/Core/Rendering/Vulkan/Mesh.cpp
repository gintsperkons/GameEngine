//Libraries
//Inbuilt
//SourceCode
#include "Mesh.h"

//<<<Privates
void Mesh::CreateVertexBuffer(std::vector<Vertex> *vertices)
{
    //Create vertex buffer
    //Information about buffer we want to create(doesn't include assigning memory)
    VkBufferCreateInfo bufferCreateInfo = {};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = sizeof(vertices[0]) * vertices->size(); //Size of buffer
    bufferCreateInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT; //Multiple types of buffer possible, this one is for vertex data
    bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; //Similar to swapchain, can share vertex buffers

    VkResult result = vkCreateBuffer(device, &bufferCreateInfo, nullptr, &vertexBuffer);
    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create a Vertex Buffer!");
    }

    //Get buffer memory requirements
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device, vertexBuffer, &memoryRequirements);

    //Allocate memory to buffer
    VkMemoryAllocateInfo memoryAllocateInfo = {};
    memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memoryAllocateInfo.allocationSize = memoryRequirements.size;
    memoryAllocateInfo.memoryTypeIndex = FindMemoryTypeIndex(memoryRequirements.memoryTypeBits, //Index of memory type on Physical Device that has required bit flags
    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);


    //Allocate memory to VkDeviceMemory
    result = vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &vertexBufferMemory);
    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate Vertex Buffer Memory!");
    }

    //Allocate memory to given vertex buffer
    vkBindBufferMemory(device, vertexBuffer, vertexBufferMemory, 0);


    //map memory to vertex buffer
    void * data;
    vkMapMemory(device, vertexBufferMemory, 0, bufferCreateInfo.size, 0, &data);
    memcpy(data, vertices->data(), (size_t)bufferCreateInfo.size);
    vkUnmapMemory(device, vertexBufferMemory);

}

uint32_t Mesh::FindMemoryTypeIndex(uint32_t allowedTypes, VkMemoryPropertyFlags properties)
{
    //Get properties of physical device memory
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
    {
        if ((allowedTypes & (1 << i)) //Index of memory type must match corresponding bit in allowedTypes
            && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) //Desired property bit flags are part of memory type's property flags
        {
            //This memory type is valid, so return its index
            return i;
        }
    }

    return 0;
}

//>>>Privates
//<<<Publics


Mesh::Mesh()
{
}

Mesh::Mesh(VkPhysicalDevice newPhysicalDevice,  VkDevice newDevice, std::vector<Vertex> *vertices)
{
    physicalDevice = newPhysicalDevice;
    device = newDevice;

    vertexCount = vertices->size();
    CreateVertexBuffer(vertices);
}

int Mesh::GetVertexCount()
{
    return vertexCount;
}

VkBuffer Mesh::GetVertexBuffer()
{
    return vertexBuffer;
}

void Mesh::DestroyVertexBuffer()
{
    vkDestroyBuffer(device, vertexBuffer, nullptr);
    vkFreeMemory(device, vertexBufferMemory, nullptr);
}

Mesh::~Mesh()
{
}

//>>>Publics