#ifndef VKAPP_H
#define VKAPP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <vector>
#include <vulkan/vulkan.h>

#define VK_USE_PLATFORM_XLIB_KHR

class VulkanApp {
    // instance
    VkApplicationInfo appInfo {};
    VkInstanceCreateInfo instanceCreateInfo {};
    VkInstance mInstance;

    // instance extensions
    std::vector<VkExtensionProperties> instanceExtensionsProperties;
    uint32_t numInstanceExtensions;

    // physical device
    VkPhysicalDevice mPhysicalDevice {VK_NULL_HANDLE};
    uint32_t physicalDeviceCount {0};

    // logical device
    VkDevice device;

    // images to present
    VkImage *_images;

    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
    uint32_t queueFamilyPropertiesCount;

    void checkInstanceExtensions();
    void checkPhysicalMemory();
    void checkQueues();
    VkResult createWindow();

    void physicalDeviceInformation();

    SDL_Window *_window {nullptr};
    size_t _windowHandle;
    SDL_vulkanSurface _surface;
    VkExtent2D _windowExtent;

    bool _isWindowCreated {false};
    VkResult createDevice();
    VkResult createSwapChain();

    public:
        VkResult init();
        void setUp();
        void run();
        void shutDown();
};

#endif

