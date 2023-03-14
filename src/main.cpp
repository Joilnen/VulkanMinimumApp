#include <vulkan/vulkan.h>
#include "app.h"

int main()
{
    VkApp vkApp;
    if(vkApp.init() == VK_SUCCESS)
        vkApp.setUp();
    vkApp.shutDown();

    return 0;
}
