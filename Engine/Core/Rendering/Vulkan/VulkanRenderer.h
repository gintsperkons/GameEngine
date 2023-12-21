#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>

class VulkanRenderer
{
	static struct QueueFamilyIndices
	{
		int graphicsFamily = -1; // Location of graphics family

		bool IsValid()
		{
			return graphicsFamily >= 0;
		}
	};

	// Vulkan components
	VkInstance vulkanInstance;
	struct
	{
		VkPhysicalDevice physicalDevice;
		VkDevice logicalDevice;
	} mainDevice;
	VkQueue graphicsQueue;

	// Vulkan functions
	//-Create functions
	void CreateInstance();
	void CreateLogicalDevice();

	//-Get functions
	void GetPhysicalDevice();

	//-Support functions
	std::vector<const char *> GetInstanceExtensions(uint32_t *extensionCount);
	bool CheckInstanceExtensionSupport(std::vector<const char *> *checkExtensions);
	bool CheckDeviceSuitable(VkPhysicalDevice device);

	//--Checker Functions
	// --Getter Functions
	QueueFamilyIndices GetQueueFamilies(VkPhysicalDevice device);

	~VulkanRenderer();
	//----
	// Window reference
	GLFWwindow *window;

public:
	int Init(GLFWwindow *window);
	void CleanUp();

	static VulkanRenderer *GetInstance();
	static void DestroyInstance();
};
