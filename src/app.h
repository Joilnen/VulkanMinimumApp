#ifndef VKAPP_H
#define VKAPP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <vector>
#include <vulkan/vulkan.h>

class VulkanApp {
    VkApplicationInfo appInfo {};
    VkInstanceCreateInfo instanceCreateInfo {};
    VkInstance mInstance;

    VkPhysicalDevice mPhysicalDevice {VK_NULL_HANDLE};
    uint32_t physicalDeviceCount {0};

    VkDevice device;

    std::vector<VkExtensionProperties> instanceExtensionsProperties;
    uint32_t numInstanceExtensions;

    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
    uint32_t queueFamilyPropertiesCount;

    void checkInstanceExtensions();
    void checkPhysicalMemory();
    void checkQueues();
    void createWindow();

    SDL_Window *_window;
    unsigned int _windowWidth;
    unsigned int _windowHeight;

    bool _isWindowCreated {false};
    void run();

    public:
        VkResult init();
        void setUp();
        void shutDown();
        VkResult createDevice();
        VkResult createSwapChain();
};

#endif

