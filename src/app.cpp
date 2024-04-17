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

    std::cout << "\n* device\n";
    createDevice();

    std::cout << "\n* queues\n";
    checkQueues();

    std::cout << "\nx create swapchain (not working yet)\n";
    createSwapChain();
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

    _window = SDL_CreateWindow("Vilkan Minimun", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_VULKAN);

    unsigned int count;
    SDL_Vulkan_GetInstanceExtensions(_window, &count, nullptr);
    vector<const char *> instanceExtensions;
    SDL_Vulkan_GetInstanceExtensions(_window, &count, instanceExtensions.data());
    instanceExtensions.push_back("VK_KHR_surface");
    instanceExtensions.push_back("VK_KHR_display");

    appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Application";
    appInfo.applicationVersion = 1.0;
    appInfo.apiVersion = VK_API_VERSION_1_3;

    // const char *instaceExtensions[] {"VK_KHR_surface", "VK_KHR_display"};
    const char *enabledLayers[] {"VK_LAYER_KHRONOS_validation"};

    instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledExtensionCount = instanceExtensions.size();
    instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
    instanceCreateInfo.enabledLayerCount = 1;
    instanceCreateInfo.ppEnabledLayerNames = enabledLayers;

    auto result = vkCreateInstance(&instanceCreateInfo, nullptr, &mInstance);

    if (result == VK_SUCCESS) {
        result = vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, nullptr);

        if (physicalDeviceCount) {
            physicalDeviceCount = 1;
            vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, &mPhysicalDevice);

        }
    }

    cout <<  "Numero de GPUs " << physicalDeviceCount << "\n";

    return result;
}

VkResult VulkanApp::createDevice() {
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

    auto result = vkCreateDevice(mPhysicalDevice, &di, nullptr, &device);
    physicalDeviceInformation();

    return result;
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
    std::cout << "QUEUE HOW MANY " << queueFamilyProperties[0].queueCount << "\n";

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

    std::cout << "Codigo de erro SWAPCHAIN " << vkCreateSwapchainKHR(device, &createSwapchainInfo, nullptr, &swapchain);
    std::cout << "\n";

    uint32_t count;
    vkGetSwapchainImagesKHR(device, swapchain, &count, nullptr);
    _images = new VkImage[count];
    auto result = vkGetSwapchainImagesKHR(device, swapchain, &count, _images);

    return result;
}

VkResult VulkanApp::createWindow() {
	// We initialize SDL and create a window with it.
    // SDL_Vulkan_GetInstanceExtensions(_window, &count, sdlInstanceExtentions);
    // for (int i = 0; i < count; i++)
    //     cout << "-> " << sdlInstanceExtentions[i] << "\n";
    /****
    Display *dpy = XOpenDisplay(NULL);

    VkXlibSurfaceCreateInfoKHR surfCreateInfo = {VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR};
    surfCreateInfo.dpy = dpy;
    surfCreateInfo.window = (Window)_windowHandle;

    int scr = DefaultScreen( dpy );
    if (!vkGetPhysicalDeviceXlibPresentationSupportKHR(mDevice->mPhysicalDevice, mDevice->mGraphicsQueue.mFamilyIdx, dpy, DefaultVisual(dpy, scr)->visualid))
    {
        cout << "Vulkan not supported on given X11 window\n";
    }

    vkCreateXlibSurfaceKHR(mInstance, &surfCreateInfo, 0, &_surface);
SDL_// Vulkan_CreateSurface(_window, (SDL_vulkanInstance)mInstance, (SDL_vulkanSurface*)&_surface);
    if (_surface)
        cout << "SURFACE IS NOT NULL\n";
    else
        cout << "SURFACE IS NULL\n";

    ****/
    return VK_SUCCESS;
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

void VulkanApp::physicalDeviceInformation() {
    VkPhysicalDeviceProperties pdp;
    vkGetPhysicalDeviceProperties(mPhysicalDevice, &pdp);

    cout << "API Version " << VK_VERSION_MAJOR(pdp.apiVersion) << ".";
    cout << VK_VERSION_MINOR(pdp.apiVersion) << "\n";

    cout << "Device name " << pdp.deviceName << "\n";
    switch (pdp.deviceType)
    {
        default:
            cout << "GPU \n";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            cout << "GPU INTEGRATED IN MD\n";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            cout << "GPU INTEGRATED IN MD\n";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            cout << "GPU INTEGRATED IN MD\n";
    }
}
