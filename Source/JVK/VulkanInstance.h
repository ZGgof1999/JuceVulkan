/*
  ==============================================================================

    VulkanInstance.h
    Created: 11 Oct 2023 1:53:22pm
    Author:  Gavin

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Wrapper/SwapChain.h"

namespace jvk
{

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
};

class VulkanInstance
{
public:
    VulkanInstance() { };
    virtual ~VulkanInstance() { };
    
protected:
    virtual void render(VkCommandBuffer& commandBuffer) { };
    
    virtual std::vector<const char*> getExtensions() { return {}; };
    virtual void createSurface() { };
    
    void initializeVulkan();
    void createInstance();
    void setupDebugMessenger();
    bool isDeviceSuitable(VkPhysicalDevice device);
    void selectPhysicalDevice();
    void createLogicalDevice();
    void createCommandPool();
    void createSwapChain();
    void createRenderPass();
    void createGraphicsPipeline();
    void createCommandBuffers();
    void createSyncObjects();
    void submitCommandBuffer(int index);
    void checkForResize();
    void execute();
    void release();
    
    // Utility
    std::vector<char> readFile(const std::string& filename);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    
    // Vulkan core components
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger; // if using validation layers
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    
    // Swapchain components
    std::unique_ptr<SwapChain> swapChain;
    
    // Graphics pipeline components
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkViewport viewport = {};
    VkRect2D scissor = {};
    
    // Drawing components
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    
    // Synchronization components
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    const int MAX_FRAMES_IN_FLIGHT = 2;
    std::vector<VkFence> imagesInFlight;
    
    // Queues
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    uint32_t graphicsQueueFamilyIndex = UINT32_MAX; // Initialized to an invalid index
    uint32_t presentQueueFamilyIndex = UINT32_MAX;  // Initialized to an invalid index
    
    // Other required members
    juce::Colour clearColor { juce::Colours::black };
    size_t totalFrames = 0;
    size_t currentFrame = 0; // For keeping track of the current frame in flight
    std::atomic<int> width { 800 };
    std::atomic<int> height { 600 };
    std::atomic<bool> windowResized { false }; // Flag for window resizing
    
};

} // jvk
