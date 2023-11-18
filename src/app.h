#ifndef VKAPP_H
#define VKAPP_H

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

    public:
        VkResult init();
        VkResult createDevice();
        void setUp();
        void shutDown();
};

#endif

