#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class VulkanValidation
{
public:
	// List of validation layers to use
// VK_LAYER_LUNARG_standard_validation = All standard validation layers
const std::vector<const char *> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

// Callback function for validation debugging (will be called when validation information record)
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
	void *pUserData);

static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger);


static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator);
private:

};

