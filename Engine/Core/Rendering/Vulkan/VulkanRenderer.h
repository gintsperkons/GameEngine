#pragma once

//Libraries
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//Inbuilt
#include <stdexcept>
#include <vector>
#include <set>
//SourceCode
#include "../Renderer.h"

class Renderer;
class VulkanRenderer : public Renderer
{
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

	struct SwapChainDetails
	{
		VkSurfaceCapabilitiesKHR surfaceCapabilities; // Surface properties, e.g. image size/extent
		std::vector<VkSurfaceFormatKHR> formats; // Surface image formats, e.g. RGBA and size of each colour
		std::vector<VkPresentModeKHR> presentationModes; // How images should be presented to screen
	
	};

	//Vulkan validation layers
	VkDebugUtilsMessengerEXT debugMessanger;
	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif

	// Vulkan components
	VkInstance vulkanInstance;
	struct
	{
		VkPhysicalDevice physicalDevice;
		VkDevice logicalDevice;
	} mainDevice;
	VkQueue graphicsQueue;
	VkQueue presentationQueue;
	VkSurfaceKHR surface;

	// Vulkan functions
	//-Create functions
	void CreateInstance();
	void CreateLogicalDevice();
	void CreateDebugCallback();
	void CreateSurface();

	//-Destroy functions

	//-Get functions

	//-Support functions
	//--Checker Functions
	bool CheckInstanceExtensionSupport(std::vector<const char *> *checkExtensions);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	bool CheckDeviceSuitable(VkPhysicalDevice device);
	bool CheckValidationLayerSupport(std::vector<const char*> *validationLayers);

	// --Getter Functions
	std::vector<const char *> GetInstanceExtensions(uint32_t *extensionCount);
	void GetPhysicalDevice();
	QueueFamilyIndices GetQueueFamilies(VkPhysicalDevice device);
	SwapChainDetails GetSwapChainDetails(VkPhysicalDevice device);

	//----
	// Window reference
	GLFWwindow *window;


	

	~VulkanRenderer();


protected:
public:
	int Init(GLFWwindow *newWindow);
	void Draw();
	void Update();
	void Destroy();
	void CleanUp();

};
