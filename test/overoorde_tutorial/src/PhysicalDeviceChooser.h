#ifndef PHYSICAL_DEVICE_CHOOSER_H
#define PHYSICAL_DEVICE_CHOOSER_H

struct PhysicalDeviceChooser {
    VkPhysicalDevice *physicalDevices;
    uint32_t physicalDevicesCount;
    VkDevice *devices;
    uint32_t devicesCount;
};

struct PhysicalDeviceChooser createPhysicalDeviceChooser();
void destroyPhysicalDeviceChooser();

#endif
