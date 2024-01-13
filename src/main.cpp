#include <vulkan/vulkan.h>
#include <iostream>
#include "app.h"

int main()
{
    VulkanApp vkApp;

    std::cout << "\n* instance\n";
    if(vkApp.init() == VK_SUCCESS) {
        vkApp.setUp();
        vkApp.run();
    }
    vkApp.shutDown();

    return 0;
}
