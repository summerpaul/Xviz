/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-24 21:19:33
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 23:02:49
 */
#include "images.h"
#include "stb_image.h"
#include <iostream>
namespace xviz
{
    UploadableImage::UploadableImage(Image *img) : image(img) {}

    Images::Images() = default;

    Images::~Images() {}

    void Images::addImage(Image *img)
    {
        m_images.push_back(UploadableImage(img));
    }

    void Images::select(size_t index)
    {
        if (this->_selectedImage != nullptr)
        {
            glDeleteTextures(1, &(this->_selectedImage->m_glindex));
            this->_selectedImage->m_glindex = 0;
        }

        if (index >= 0 && index < this->m_images.size())
        {
            this->_selectedImage = &this->m_images[index];
            uploadSelectedImage();
        }
    }

    Image *Images::selected()
    {
        if (this->_selectedImage != nullptr)
        {
            return this->_selectedImage->image;
        }

        return nullptr;
    }

    bool Images::hasImages() const
    {
        return this->m_images.size() > 0;
    }

    void Images::uploadSelectedImage()
    {
        auto img = this->_selectedImage;
        auto dataSize = img->image->m_size[0] * img->image->m_size[1] * 4;
        if (img->image->m_data == nullptr)
        {
            img->image->m_data = new unsigned char[dataSize];
        }

        memset(img->image->m_data, 0, dataSize);

        for (Layer *layer : img->image->m_layers)
        {
            if (!layer->m_visible)
            {
                continue;
            }

            for (int y = 0; y < img->image->m_size[1]; ++y)
            {
                for (int x = 0; x < img->image->m_size[0]; ++x)
                {
                    auto p = (x * img->image->m_size[1] + y);
                    for (int b = 0; b < layer->m_bpp; b++)
                    {
                        img->image->m_data[p * 4 + b] += layer->m_data[p * layer->m_bpp + b];
                    }
                    if (layer->m_bpp < 4)
                    {
                        img->image->m_data[p * 4 + 3] = 255;
                    }
                }
            }
        }

        if (img->m_glindex == 0)
        {
            glGenTextures(1, &(img->m_glindex));
        }

        std::cout << "img->m_glindex " << img->m_glindex << std::endl;

        glBindTexture(GL_TEXTURE_2D, img->m_glindex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        GLint format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, img->image->m_size[0], img->image->m_size[1], 0, format, GL_UNSIGNED_BYTE, img->image->m_data);
        std::cout << "width is " << img->image->m_size[0] <<"height is " <<  img->image->m_size[1]  << std::endl;
    }

}
