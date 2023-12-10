#include <iostream>
#include <cassert>
#include "app.h"

using namespace std;

void VulkanApp::setUp() {
    std::cout << "\n* extensions\n";
    checkInstanceExtensions();
    std::cout << "\n";

    std::cout << "\n* memory\n";
    checkPhysicalMemory();

    std::cout << "\n* queues\n";
    checkQueues();

    std::cout << "\n* create window\n";
    createWindow();
}

void VulkanApp::shutDown() {
    if (vkDeviceWaitIdle(device) == VK_SUCCESS)  {
        vkDestroyDevice(device, nullptr);
        vkDestroyInstance(mInstance, nullptr);
    }
}

void VulkanApp::checkInstanceExtensions() {
    vkEnumerateInstanceExtensionProperties(nullptr, &numInstanceExtensions, nullptr);

    std::cout << "NUM EXT " << numInstanceExtensions << "\n";
    if (numInstanceExtensions) {
        instanceExtensionsProperties.resize(numInstanceExtensions);
        vkEnumerateInstanceExtensionProperties(nullptr, &numInstanceExtensions, instanceExtensionsProperties.data());
        for (auto& a : instanceExtensionsProperties)
            std::cout << a.extensionName << "\n";
    }
}

VkResult VulkanApp::init() {
    appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Application";
    appInfo.applicationVersion = 1.0;
    appInfo.apiVersion = VK_API_VERSION_1_3;

    const char *instaceExtensions[] {"VK_KHR_surface", "VK_KHR_display"};
    const char *enabledLayers[] {"VK_LAYER_KHRONOS_validation"};

    instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledExtensionCount = 2;
    instanceCreateInfo.ppEnabledExtensionNames = instaceExtensions;
    instanceCreateInfo.enabledLayerCount = 1;
    instanceCreateInfo.ppEnabledLayerNames = enabledLayers;

    auto result = vkCreateInstance(&instanceCreateInfo, nullptr, &mInstance);

    if (result == VK_SUCCESS) {
        result = vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, nullptr);

        if (physicalDeviceCount) {
            physicalDeviceCount = 1;
            vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, &mPhysicalDevice);

            const float priority = 1.0f;

            VkDeviceQueueCreateInfo qi {};
            qi.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            qi.queueFamilyIndex = 0;
            qi.queueCount = 1;
            qi.pQueuePriorities = &priority;

            const char *deviceExtensions[] {"VK_KHR_swapchain"};

            VkDeviceCreateInfo  di {};
            di.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            di.queueCreateInfoCount = 1;
            di.pQueueCreateInfos = &qi;
            di.enabledExtensionCount = 1;
            di.ppEnabledExtensionNames = deviceExtensions;

            result = vkCreateDevice(mPhysicalDevice, &di, nullptr, &device);
        }
    }

    cout <<  "Numero de GPUs " << physicalDeviceCount << "\n";

    return result;
}

VkResult VulkanApp::createDevice() {

    return (VkResult) 0;
}

void VulkanApp::checkPhysicalMemory() {
    VkPhysicalDeviceMemoryProperties p;
    vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &p);

    std::cout << "MEM COUNT " << p.memoryTypeCount << "\n\n";
    auto count = 0;
    for (auto& a : p.memoryTypes) {
        if (a.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
        {
            std::cout << "COUNTER " << count++ << "\n";
            std::cout << "HEAP INDEX " << a.heapIndex << "\n";
            std::cout << "VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT\n";
            auto count2 = 0;
            for (auto m : p.memoryHeaps)
                if (count2++ == a.heapIndex)
                    std::cout << "SIZE " << p.memoryHeaps[a.heapIndex].size << "\n\n";

        }
        if (a.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
        {
            std::cout << "COUNTER " << count++ << "\n";
            std::cout << "HEAP INDEX " << a.heapIndex << "\n";
            std::cout << "VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT\n";
            auto count2 = 0;
            for (auto m : p.memoryHeaps)
                if (count2++ == a.heapIndex)
                    std::cout << "SIZE " << p.memoryHeaps[a.heapIndex].size << "\n\n";
        }
        if (a.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
        {
            std::cout << "COUNTER " << count++ << "\n";
            std::cout << "HEAP INDEX " << a.heapIndex << "\n";
            std::cout << "VK_MEMORY_PROPERTY_HOST_COHERENT_BIT\n";
            auto count2 = 0;
            for (auto m : p.memoryHeaps)
                if (count2++ == a.heapIndex)
                    std::cout << "SIZE " << p.memoryHeaps[a.heapIndex].size << "\n\n";
        }
        if (a.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
        {
            std::cout << "COUNTER " << count++ << "\n";
            std::cout << "HEAP INDEX " << a.heapIndex << "\n";
            std::cout << "VK_MEMORY_PROPERTY_HOST_CACHED_BIT\n";
            auto count2 = 0;
            for (auto m : p.memoryHeaps)
                if (count2++ == a.heapIndex)
                    std::cout << "SIZE " << p.memoryHeaps[a.heapIndex].size << "\n\n";
        }
        if (a.propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
        {
            std::cout << "COUNTER " << count++ << "\n";
            std::cout << "HEAP INDEX " << a.heapIndex << "\n";
            std::cout << "VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT\n";
            auto count2 = 0;
            for (auto m : p.memoryHeaps) {
                if (count2++ == a.heapIndex)
                    std::cout << "SIZE " << p.memoryHeaps[a.heapIndex].size << "\n";
            }
        }
    }
    std::cout << "HEAP MEM COUNT " << p.memoryHeapCount << "\n";
}

void VulkanApp::checkQueues() {
    vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &queueFamilyPropertiesCount, nullptr);
    queueFamilyProperties.resize(queueFamilyPropertiesCount);
    vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &queueFamilyPropertiesCount, queueFamilyProperties.data());
    std::cout << "QUEUE HOW MANY " << queueFamilyPropertiesCount << "\n";
    for (auto& a : queueFamilyProperties) {
        if (a.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            std::cout << "QUEUE N " << a.queueCount << "\n";
            std::cout << "QUEUE TYPE VK_QUEUE_GRAPHICS_BIT\n";
        }

        if (a.queueFlags & VK_QUEUE_COMPUTE_BIT) {
            std::cout << "QUEUE N " << a.queueCount << "\n";
            std::cout << "QUEUE TYPE VK_QUEUE_COMPUTE_BIT\n";
        }

        if (a.queueFlags & VK_QUEUE_TRANSFER_BIT) {
            std::cout << "QUEUE N " << a.queueCount << "\n";
            std::cout << "QUEUE TYPE VK_QUEUE_TRANSFER_BIT\n";
        }

        if (a.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) {
            std::cout << "QUEUE N " << a.queueCount << "\n";
            std::cout << "QUEUE TYPE VK_QUEUE_SPARSE_BINDING_BIT\n";
        }
    }
}

VkResult VulkanApp::createSwapChain() {
    VkSwapchainCreateInfoKHR createSwapchainInfo {};
    createSwapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createSwapchainInfo.surface = _surface;
    createSwapchainInfo.minImageCount = 4;
    createSwapchainInfo.imageFormat = VK_FORMAT_R8G8B8A8_SRGB;
    createSwapchainInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    createSwapchainInfo.imageExtent = _windowExtent;
    createSwapchainInfo.imageArrayLayers = 1;
    createSwapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createSwapchainInfo.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;

    // vkCreateSwapchainKHR()
    VkSwapchainKHR swapchain = nullptr;
    uint32_t count;
    vkGetSwapchainImagesKHR(device, swapchain, &count, nullptr);
    _images = new VkImage[count];
    vkGetSwapchainImagesKHR(device, swapchain, &count, _images);

    return (VkResult) 0;
}

void VulkanApp::createWindow() {
	// We initialize SDL and create a window with it.
	SDL_Init(SDL_INIT_VIDEO);

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN);

	_window = SDL_CreateWindow(
        "Vulkan Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        _windowExtent.width,
        _windowExtent.height,
        window_flags
	);

	_isWindowCreated = true;

    SDL_Vulkan_CreateSurface(_window, mInstance, &_surface);
}

/****
void VulkanEngine::cleanup()
{
	if (_isInitialized) {

		SDL_DestroyWindow(_window);
	}
}

void VulkanEngine::draw()
{
	//nothing yet
}
****/

void VulkanApp::run() {
	SDL_Event e;
	bool bQuit = false;

	//main loop
	while (!bQuit) {
        while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) bQuit = true;
		}
		// draw();
	}
}

