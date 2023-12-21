#include "VulkanRenderer.h"
#include <cstring>

VulkanRenderer *instance;
VulkanRenderer *VulkanRenderer::GetInstance()
{
	if (instance == nullptr)
		instance = new VulkanRenderer();
	return instance;
}

void VulkanRenderer::DestroyInstance()
{
	if (instance != nullptr)
		delete instance;
}


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

	if (!CheckInstanceExtensionSupport(&instanceExtensions))
	{
		throw std::runtime_error("VkInstance doe not support required extensions!");
	}

	createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();

	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;

	//Create instance
	VkResult result = vkCreateInstance(&createInfo, nullptr, &vulkanInstance);
	//Check if instance creation was successful
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create a Vulkan instance!");
	}

}

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



	return indices.IsValid();
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

		//Check if queue family indices are in a valid state, stop searching if so
		if (indices.IsValid())
		{
			break;
		}
	}


	return indices;
}

void VulkanRenderer::CreateLogicalDevice()
{
	//Get queue family indices for the chosen physical device
	QueueFamilyIndices indices = GetQueueFamilies(mainDevice.physicalDevice);

	//Queue creation information, and how many queues to create
	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily; //Index of the family to create a queue from
	queueCreateInfo.queueCount = 1; //Number of queues to create
	float priority = 1.0f;
	queueCreateInfo.pQueuePriorities = &priority; //Vulkan needs to know how to handle multiple queues, so decide priority (1 = highest priority)

	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1; //Number of queue create infos
	deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo; //List of queue create infos so device can create required queues
	deviceCreateInfo.enabledExtensionCount = 0; //Number of enabled logical device extensions
	deviceCreateInfo.ppEnabledExtensionNames = nullptr; //List of enabled logical device extensions

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
}

int VulkanRenderer::Init(GLFWwindow *newWindow)
{
	this->window = newWindow;

	try
	{
		CreateInstance();
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

VulkanRenderer::~VulkanRenderer()
{
	CleanUp();
}

void VulkanRenderer::CleanUp()
{
	vkDestroyDevice(mainDevice.logicalDevice, nullptr);
	vkDestroyInstance(vulkanInstance, nullptr);
}
