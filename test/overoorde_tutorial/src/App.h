#ifndef HELLO_TRIANGLE_H
#define HELLO_TRIANGLE_H

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <map>
#include <optional>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enabledValidationLayers {true};
#else
    const bool enabledValidationLayers {false};
#endif

struct QueueFamiliesIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

class App {
    GLFWwindow *window {nullptr};
    VkInstance instance { VK_NULL_HANDLE };
    VkPhysicalDevice physicalDevice {VK_NULL_HANDLE};
    VkDevice device { VK_NULL_HANDLE } ;
    VkQueue graphicsQueue { VK_NULL_HANDLE } ;
    VkQueue presentQueue { VK_NULL_HANDLE } ;
    VkSurfaceKHR surface { VK_NULL_HANDLE };

    void createInstance();
    void initWindow();
    void pickPhysicalDevice();
    int rateDeviceSuitability(VkPhysicalDevice device);
    void initVulkan();
    void mainLoop();
    void cleanup();
    std::vector<const char *> getRequiredExtenstions();
    uint32_t ind;
    QueueFamiliesIndices findQueueFamilies();
    bool isDeviceSuitable();
    void createLogicalDevice();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
        void *pUserData
    );
    public:
        void run();
};

#endif
