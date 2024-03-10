

#ifndef FILTER_IMAGE_MANAGER_H
#define FILTER_IMAGE_MANAGER_H

#include "image.hpp"
#include <vector>

enum ShareStatus
{
    RELEASED = -1,
    NO_SHARE = 0,
    REUSE_USING = 1,
    REUSE_ENABLE = 2
};



class ImageManager
{
private:
    std::vector<std::pair<ShareStatus, Image>> image_list_;
public:
    ~ImageManager();
    int ClearAllImages();
    Image CreateImage(const std::uint32_t width, const std::uint32_t height, const std::uint32_t channel, const bool no_share = false);
    Image CreateImage(void* data, const std::uint32_t width, const std::uint32_t height, const std::uint32_t channel, const bool no_share = false);
    void UpdateImageMemoryStatus(Image img, const ShareStatus status);
};

#endif //FILTER_IMAGE_MANAGER_H
