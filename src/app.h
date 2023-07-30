#ifndef VKAPP_H
#define VKAPP_H

#include <vector>
#include <vulkan/vulkan.h>

class VkApp {
    VkApplicationInfo appInfo {  };
    VkInstanceCreateInfo instanceCreateInfo {  };
    VkInstance mInstance;

    VkPhysicalDevice mPhysicalDevice {nullptr};
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
        void setUp();
        void shutDown();
};

#endif

