/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-24 21:19:33
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 21:29:30
 */
#ifndef IMAGES_H
#define IMAGES_H

#include <glad/gl.h>

#include "image.h"
#include <map>
namespace xviz
{
    class UploadableImage
    {
    public:
        UploadableImage(Image *img);
        GLuint m_glindex = 0;
        Image *image = nullptr;
    };

    class Images
    {
        UploadableImage *_selectedImage = nullptr;

    public:
        Images();
        virtual ~Images();

        std::vector<UploadableImage> m_images;

        void addImage(Image *img);
        void select(size_t index);
        Image *selected();
        bool hasImages() const;
        void uploadSelectedImage();
    };
}
#endif // IMAGES_H
