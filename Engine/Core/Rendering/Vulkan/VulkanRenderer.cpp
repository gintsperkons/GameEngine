#include "VulkanRenderer.h"
#include "VulkanValidation.h""
#include <cstring>
#include <iostream>


//<<<Privates

//<--Create Functions
void VulkanRenderer::CreateInstance()
{
	//Information about the application
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan Voxels";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
	appInfo.pEngineName = "Vulkan Voxels Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
	appInfo.apiVersion = VK_API_VERSION_1_3;


	//Information for vulkan instance
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
	std::vector<const char *> instanceExtensions = GetInstanceExtensions(&glfwExtensionCount);
	if (enableValidationLayers)
	{
		instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}



	if (!CheckInstanceExtensionSupport(&instanceExtensions))
	{
		throw std::runtime_error("VkInstance doe not support required extensions!");
	}

	createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();

	//Check validation layer support
	std::vector<const char *> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
	};
	if (enableValidationLayers && !CheckValidationLayerSupport(&validationLayers))
	{
		throw std::runtime_error("Validation layers requested, but not available!");
	}

	//Set up validation layers to use
	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
		createInfo.ppEnabledLayerNames = nullptr;
	}

	//Create instance
	VkResult result = vkCreateInstance(&createInfo, nullptr, &vulkanInstance);
	//Check if instance creation was successful
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create a Vulkan instance!");
	}

}

void VulkanRenderer::CreateLogicalDevice()
{
	//Get queue family indices for the chosen physical device
	QueueFamilyIndices indices = GetQueueFamilies(mainDevice.physicalDevice);

	//Vector for queue creation information, and set for family indices
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> queueFamilyIndices = { indices.graphicsFamily, indices.presentationFamily };

	for (int queueFamilyIndex : queueFamilyIndices)
	{
		//Queue creation information, and how many queues to create
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamilyIndex; //Index of the family to create a queue from
		queueCreateInfo.queueCount = 1; //Number of queues to create
		float priority = 1.0f;
		queueCreateInfo.pQueuePriorities = &priority; //Vulkan needs to know how to handle multiple queues, so decide priority (1 = highest priority)

		queueCreateInfos.push_back(queueCreateInfo); //Push info to back of queue create info vector
	}


	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()); //Number of queue create infos
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data(); //List of queue create infos so device can create required queues
	deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()); //Number of enabled logical device extensions
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data(); //List of enabled logical device extensions



	//Physical device features the logical device will be using
	VkPhysicalDeviceFeatures deviceFeatures = {};
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures; //Physical device features logical device will use

	VkResult result = vkCreateDevice(mainDevice.physicalDevice, &deviceCreateInfo, nullptr, &mainDevice.logicalDevice);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create a logical device!");
	}
	//Create queue for graphics family
	vkGetDeviceQueue(mainDevice.logicalDevice, indices.graphicsFamily, 0, &graphicsQueue);
	vkGetDeviceQueue(mainDevice.logicalDevice, indices.presentationFamily, 0, &presentationQueue);
}

void VulkanRenderer::CreateDebugCallback()
{
	// Only create callback if validation enabled
	if (!enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = VulkanValidation::DebugCallback;
	createInfo.pUserData = nullptr; // Optional									// Pointer to callback function itself


	// Create debug callback with custom create function
	VkResult result = VulkanValidation::CreateDebugUtilsMessengerEXT(vulkanInstance, &createInfo, nullptr, &debugMessanger);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Debug Callback!");
	}
}

void VulkanRenderer::CreateSurface()
{
	//Create surface (creates a surface create info struct, runs the create surface function, returns result)
	VkResult result = glfwCreateWindowSurface(vulkanInstance, window, nullptr, &surface);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create a surface!");
	}
}


//-->Create Functions


//<--Support Functions

//<==Checker Functions

bool VulkanRenderer::CheckInstanceExtensionSupport(std::vector<const char *> *checkExtensions)
{
	//Get number of extensions to create array of correct size
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	//Create a list of VkExtensionProperties using count
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	//Check if given extensions are in list of available extensions
	for (const auto &checkExtension : *checkExtensions)
	{
		bool hasExtension = false;
		for (const auto &extension : extensions)
		{
			if (strcmp(checkExtension, extension.extensionName))
			{
				hasExtension = true;
				break;
			}
		}

		if (!hasExtension)
			return false;
	}
	return true;
}

bool VulkanRenderer::CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
	//Get device extension count
	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	//If no extensions found, return failure
	if (extensionCount == 0)
		return false;

	//Populate list of extensions
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, extensions.data());

	//Check for extension
	for (const auto &deviceExtension : deviceExtensions)
	{
		bool hasExtension = false;
		for (const auto &extension : extensions)
		{
			if (strcmp(deviceExtension, extension.extensionName) == 0)
			{
				hasExtension = true;
				break;
			}
		}

		if (!hasExtension)
			return false;
	}

	return true;
}

bool VulkanRenderer::CheckDeviceSuitable(VkPhysicalDevice device)
{
	//Information about the device itself (ID, name, type, vendor, etc)
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	//Information about what the device can do (geo shader, tess shader, wide lines, etc)
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	//Check if device is suitable
	//Check for queue families

	QueueFamilyIndices indices = GetQueueFamilies(device);

	bool extensionsSupported = CheckDeviceExtensionSupport(device);
	bool swapChainValid = false;
	SwapChainDetails swapChainDetails = GetSwapChainDetails(device);
	swapChainValid = !swapChainDetails.formats.empty() && !swapChainDetails.presentationModes.empty();



	return indices.IsValid() && extensionsSupported && swapChainValid;
}

bool VulkanRenderer::CheckValidationLayerSupport(std::vector<const char *> *validationLayers)
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


	for (const char *layerName : *(validationLayers))
	{
		bool layerFound = false;

		for (const auto &layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			return false;
		}
	}

	return true;
}

//==>Checker Functions

//<==Get Functions

std::vector<const char *> VulkanRenderer::GetInstanceExtensions(uint32_t *extensionCount)
{
	//Create list to hold instance extensions
	std::vector<const char *> instanceExtensions = std::vector<const char *>();

	//Set up extensions instance will use
	*(extensionCount) = 0; //GLFW may require multiple extensions
	const char **glfwExtensions; //Extensions passed as array of cstrings, so need pointer to pointer

	//Get GLFW extensions
	glfwExtensions = glfwGetRequiredInstanceExtensions(extensionCount);

	//Add GLFW extensions to list of extensions
	for (size_t i = 0; i < *(extensionCount); i++)
	{
		instanceExtensions.push_back(glfwExtensions[i]);
	}

	return instanceExtensions;
}

void VulkanRenderer::GetPhysicalDevice()
{
	//Enumerate physical devices the vkInstance can access
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, nullptr);

	//If no devices available, then none support Vulkan!
	if (deviceCount == 0)
	{
		throw std::runtime_error("Can't find GPUs that support Vulkan Instance!");
	}

	//Get list of physical devices
	std::vector<VkPhysicalDevice> deviceList(deviceCount);
	vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, deviceList.data());

	for (const auto &device : deviceList)
	{
		if (CheckDeviceSuitable(device))
		{
			mainDevice.physicalDevice = device;
			break;
		}
	}
}

VulkanRenderer::QueueFamilyIndices VulkanRenderer::GetQueueFamilies(VkPhysicalDevice device)
{
	VulkanRenderer::QueueFamilyIndices indices;

	//Get all queue family property info for the given device
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyList.data());

	//Go through each queue family and check if it has at least 1 of the required types of queue
	int i = 0;
	for (const auto &queueFamily : queueFamilyList)
	{
		//First check if queue family has at least 1 queue in that family (could have no queues)
		//Queue can be multiple types defined through bitfield. Need to bitwise AND with VK_QUEUE_*_BIT to check if has required type
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i; //If queue family is valid, then get index

		}
		i++;

		//Check if queue family supports presentation
		VkBool32 presentationSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentationSupport);

		//Check if queue is presentation type
		if (queueFamily.queueCount > 0 && presentationSupport)
		{
			indices.presentationFamily = i;
		}


		//Check if queue family indices are in a valid state, stop searching if so
		if (indices.IsValid())
		{
			break;
		}
	}


	return indices;
}

VulkanRenderer::SwapChainDetails VulkanRenderer::GetSwapChainDetails(VkPhysicalDevice device)
{
	SwapChainDetails swapChainDetails;

	//Capabilities
	//Get surface capabilities for the given surface on the given physical device
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &swapChainDetails.surfaceCapabilities);

	//Formats
	uint32_t formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	//If formats returned, get list of formats
	if (formatCount != 0)
	{
		swapChainDetails.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, swapChainDetails.formats.data());
	}

	//Presentation Modes

	uint32_t presentationCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentationCount, nullptr);

	//If presentation modes returned, get list of presentation modes
	if (presentationCount != 0)
	{
		swapChainDetails.presentationModes.resize(presentationCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentationCount, swapChainDetails.presentationModes.data());
	}


	return swapChainDetails;
}


//==>Get Functions


//-->Support Functions









VulkanRenderer::~VulkanRenderer()
{
	CleanUp();
}
//>>>Privates




//<<<Publics
int VulkanRenderer::Init(GLFWwindow *newWindow)
{
	this->window = newWindow;

	try
	{
		CreateInstance();
		CreateDebugCallback();
		CreateSurface();
		GetPhysicalDevice();
		CreateLogicalDevice();
	}
	catch (const std::runtime_error &e)
	{
		printf("ERROR: %s\n", e.what());
		return EXIT_FAILURE;
	}

	return 0;
}

void VulkanRenderer::Draw()
{}

void VulkanRenderer::Update()
{}

void VulkanRenderer::Destroy()
{}

void VulkanRenderer::CleanUp()
{
	vkDestroySurfaceKHR(vulkanInstance, surface, nullptr);
	if (enableValidationLayers)
	{
		VulkanValidation::DestroyDebugUtilsMessengerEXT(vulkanInstance, debugMessanger, nullptr);
	}
	vkDestroyDevice(mainDevice.logicalDevice, nullptr);
	vkDestroyInstance(vulkanInstance, nullptr);
}

//>>>Publics

