
#include "VulkanDescriptorPool.h"

VulkanDescriptorPool::VulkanDescriptorPool(VkDevice& device)
{
    VkDescriptorPoolSize poolSizes[2];
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = 20;
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = 20;

    VkDescriptorPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.maxSets = 20;
    poolInfo.poolSizeCount = 2;
    poolInfo.pPoolSizes = poolSizes;

    auto err = vkCreateDescriptorPool(device, &poolInfo, nullptr, &pool);
    assert(!err);
}
