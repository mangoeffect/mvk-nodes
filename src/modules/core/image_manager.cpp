
#include "image_manager.hpp"

ImageManager::~ImageManager()
{
    ClearAllImages();
}

int ImageManager::ClearAllImages()
{
    image_list_.clear();
}

Image ImageManager::CreateImage(const std::uint32_t width, const std::uint32_t height, const std::uint32_t channel,
                                 const bool no_share)
{
    void* data = new std::uint8_t[width * height * channel]();
    return CreateImage(data, width, height, channel, no_share);
}

Image ImageManager::CreateImage(void *data, const std::uint32_t width, const std::uint32_t height,
                                 const std::uint32_t channel, const bool no_share)
{
    auto status = no_share ? ShareStatus::NO_SHARE: ShareStatus::REUSE_USING;
    Image img = Image(Size(width, height), channel, (std::uint8_t*)data);
    image_list_.push_back({status, img});

    return img;
}

void ImageManager::UpdateImageMemoryStatus(Image img, const ShareStatus status)
{
    for(auto& [status, image]: image_list_)
    {
        if(status != ShareStatus::NO_SHARE && image.Ptr<uchar>(0,0) == img.Ptr<uchar>(0,0))
        {
            status = status;
        }
    }
}


