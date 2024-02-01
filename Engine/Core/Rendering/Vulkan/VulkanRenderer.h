#pragma once

//Libraries
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <GLM/glm.hpp>
//Inbuilt
#include <stdexcept>
#include <vector>
#include <set>
#include <array>
//SourceCode
#include "Mesh.h"
#include "../RendererStructures.h"
#include "Utilities.h"
#include "../Renderer.h"

class Renderer;
class VulkanRenderer : public Renderer
{
	//Render Setting
	glm::vec4 clearColor;

	int currentFrame = 0;

	//Vulkan validation layers
	VkDebugUtilsMessengerEXT debugMessanger;
	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif

	//Scene Objects
	Mesh firstMesh;

	// Vulkan components
		// - Main Components
	VkInstance vulkanInstance;
	struct
	{
		VkPhysicalDevice physicalDevice;
		VkDevice logicalDevice;
	} mainDevice;
	VkQueue graphicsQueue;
	VkQueue presentationQueue;
	VkSurfaceKHR surface;
	VkSwapchainKHR swapchain;
	std::vector<SwapChainImage> swapChainImages;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	std::vector<VkCommandBuffer> commandBuffers;


	// - Pipeline
	VkPipeline graphicsPipeline;
	VkPipelineLayout pipelineLayout;
	VkRenderPass renderPass;

	// - Pools
	VkCommandPool commandPool;

	//Utility variables
	VkFormat swapchainImageFormat;
	VkExtent2D swapchainExtent;

	//Syncronisation 
	std::vector<VkSemaphore> imageAvailable;
	std::vector<VkSemaphore> renderFinished;
	std::vector<VkFence> drawFences; // CPU-GPU syncronisation, wait until GPU is done with resource



	// Vulkan functions
	//-Create functions
	void CreateInstance();
	void CreateLogicalDevice();
	void CreateDebugCallback();
	void CreateSurface();
	void CreateSwapChain();
	void CreateRenderPass();
	void CreateGraphicsPipeline();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateCommandBuffers();
	void CreateSyncronisation();

	//-Record functions
	void RecordCommands();


	//-Support functions
	//--Checker Functions
	bool CheckInstanceExtensionSupport(std::vector<const char *> *checkExtensions);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	bool CheckDeviceSuitable(VkPhysicalDevice device);
	bool CheckValidationLayerSupport(std::vector<const char*> *validationLayers);

	// --Getter Functions
	void GetPhysicalDevice();
	std::vector<const char *> GetInstanceExtensions(uint32_t *extensionCount);
	QueueFamilyIndices GetQueueFamilies(VkPhysicalDevice device);
	SwapChainDetails GetSwapChainDetails(VkPhysicalDevice device);

	// --Choose Functions
	VkSurfaceFormatKHR ChooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
	VkPresentModeKHR ChooseBestPresentationMode(const std::vector<VkPresentModeKHR> &availablePresentationModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

	// --Create Functions
	VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	VkShaderModule CreateShaderModule(const std::vector<char> &code);

	//----
	// Window reference
	GLFWwindow *window;


	

	~VulkanRenderer();


protected:
public:
	VulkanRenderer();
	int Init(GLFWwindow *newWindow);
	void Draw();
	void Update();
	void Destroy();
	void CleanUp();

};
