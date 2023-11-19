#include <vulkan/vulkan.h>
#include "app.h"

int main()
{
    VulkanApp vkApp;
    if(vkApp.init() == VK_SUCCESS) {
        vkApp.setUp();
        vkApp.run();
    }
    vkApp.shutDown();

    return 0;
}
