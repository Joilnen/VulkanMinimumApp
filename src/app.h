#ifndef VKAPP_H
#define VKAPP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <vector>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

using namespace glm;

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
    VkPhysicalDevice phyDevice { VK_NULL_HANDLE };
    uint32_t physicalDeviceCount { 0 };

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

    SDL_Window *_window { nullptr };
    size_t _windowHandle;
    SDL_vulkanSurface _surface;
    VkExtent2D _windowExtent;

    bool _isWindowCreated { false };
    VkResult createDevice();
    VkResult createSwapChain();

    typedef struct {
        uint32_t graphics_family;
        uint32_t present_family;
        bool has_graphics_family;
        bool has_present_family;
    } QueueFamilyIndices;

    typedef struct {
        VkSurfaceCapabilitiesKHR capabilities;
        uint32_t formats_count;
        uint32_t present_modes_count;
        VkSurfaceFormatKHR* formats;
        VkPresentModeKHR* present_modes;
    } SwapChainSupportDetails;

    typedef struct {
        vec2 pos;
        vec3 color;
    } Vertex;

    typedef struct {
        mat4 model;
        mat4 view;
        mat4 proj;
    } UniformBufferObject;

    public:
        VkResult init();
        void setUp();
        void run();
        void shutDown();
};

#endif

