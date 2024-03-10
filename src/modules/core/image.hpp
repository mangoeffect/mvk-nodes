#ifndef MANGO_CORE_IMAGE_H
#define MANGO_CORE_IMAGE_H

#include "common_data.hpp"
#include <vector>
#include <cassert>
#include <array>

using namespace std;

typedef unsigned short uattr;
typedef unsigned char uchar;
typedef uchar Vec3b[3];
typedef uchar Vec4b[4];
typedef float Vec3f[3];
typedef float Vec4f[4];

#define UNITATTR(id, size) ((uattr)((id << 8) | size))
#define UNITATTR_ID(v) ((uattr)(v >> 8))
#define UNITATTR_SIZE(v) ((uattr)(v & 0x00ff))  //calculate the size of one element


enum IMAGE_TYPE
{
    IMAGE_8UC1 = UNITATTR(0, 1),
    IMAGE_8UC2 = UNITATTR(1, 2),
    IMAGE_8UC3 = UNITATTR(2, 3),
    IMAGE_8UC4 = UNITATTR(3, 4),
    IMAGE_32FC1 = UNITATTR(4, 4),
    IMAGE_32FC2 = UNITATTR(5, 8),
    IMAGE_32FC3 = UNITATTR(6, 12),
    IMAGE_32FC4 = UNITATTR(7, 16)
};

enum BORDER_TYPE
{
    NONE = 0,               ///<不填充
    MIRROR = 1,             ///<默认 镜像， 123 | 321
    CONSTANT = 2,           ///<常数填充，  123 | ccc
    REPLICATE = 3,          ///<边界复制,   123 | 333
};

enum CONVERT_TYPE
{
    RGB2GRAY = 0,
    RGB2BGR = 1,
    RGB2RGBA = 2,
    RGB2HSV = 3
};

class Image;

class RePtr
{
private:

    friend class Image;
    RePtr() : count(1) { }
    ~RePtr() {}
    int count;
};

class Image
{
private:
    uchar *ptr_;
    Rect origin_rect_;
    Rect my_rect_;
    uattr unit_type_;
    bool owner_;

    int rows;
    int cols;
    RePtr* re_ptr_;
public:
    Image();

    Image(const Size &size, uattr type);

    Image(const Size &size, uattr type, uchar* data);

    Image(const Image &other);
    Image(const Image &&other);

    Image& operator=(const Image &other);
    Image operator()(const Rect &roi);

    virtual ~Image();

private:
    void Release();
public:
    void Create(const Size &size, uattr type);
    void CopyTo(Image &other) const;
    Image Clone() const;
    Image CopyWithBorder(const size_t border_size,
                         const BORDER_TYPE& border_type = BORDER_TYPE::MIRROR,
                         const std::array<uint8_t, 3>& const_border = {0, 0, 0});

    Image Convert(const CONVERT_TYPE& type) const;
public:
    template<typename E>
    E& At(int x, int y);

    template<typename E>
    E& At(const Point &point);

    template<typename E>
    E* Ptr(int x, int y);

    template<typename E>
    E* Ptr(const Point &point);

    std::uint8_t Channels() const;

    bool IsEmpty() const;

    Size GetSize() const;

    uattr GetType() const;
};

Image LoadImage(const char* img_path);

int WriteImage(Image img, const char* img_path);

Image ConvertType(Image src, const CONVERT_TYPE& type);


#endif //MANGO_CORE_IMAGE_H
