
#pragma once

//Libraries
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <GLM/glm.hpp>
//Inbuilt
#include <vector>
//SourceCode


    const int MAX_FRAME_DRAWS = 2;
	const std::vector<const char *> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	struct QueueFamilyIndices
	{
		int graphicsFamily = -1; // Location of graphics family
		int presentationFamily = -1; // Location of presentation family

		bool IsValid()
		{
			return graphicsFamily >= 0 && presentationFamily >=0;
		}
	};

	//Vertex data representation
	struct Vertex 
	{
		glm::vec3 pos; // Vertex position (x, y, z)
		glm::vec3 col; // Vertex colour (r, g, b)
	};

	struct SwapChainDetails
	{
		VkSurfaceCapabilitiesKHR surfaceCapabilities; // Surface properties, e.g. image size/extent
		std::vector<VkSurfaceFormatKHR> formats; // Surface image formats, e.g. RGBA and size of each colour
		std::vector<VkPresentModeKHR> presentationModes; // How images should be presented to screen
	
	};

	struct SwapChainImage
	{
		VkImage image;
		VkImageView imageView;
	};