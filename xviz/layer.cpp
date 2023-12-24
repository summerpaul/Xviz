/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-24 21:19:33
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 22:47:45
 */
#include "layer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace xviz
{
    Layer::Layer()
    {
        m_size[0] = m_size[1] = 0;
    }

    void Layer::setSize(int size[2])
    {
        byte pixel[4] = {255, 255, 255, 255};
        setSize(size[0], size[1], pixel);
    }

    void Layer::setSize(int w, int h)
    {
        byte pixel[4] = {255, 255, 255, 255};
        setSize(w, h, pixel);
    }

    void Layer::setSize(int size[2], const byte pixel[])
    {
        setSize(size[0], size[1], pixel);
    }

    void Layer::setSize(int w, int h, const byte pixel[])
    {
        this->m_offset[0] = 0;
        this->m_offset[1] = 0;

        this->m_bpp = 4;

        if (w != m_size[0] || h != m_size[1])
        {
            this->m_size[0] = w;
            this->m_size[1] = h;

            if (this->m_data != nullptr)
            {
                delete[] this->m_data;
            }

            this->m_data = new unsigned char[dataSize()];
        }

        for (int y = 0; y < this->m_size[1]; y++)
        {
            for (int x = 0; x < this->m_size[0]; x++)
            {
                setPixel<4>(x, y, pixel);
            }
        }
    }

    int Layer::dataSize() const
    {
        return this->m_size[0] * this->m_size[1] * this->m_bpp;
    }

    Layer *Layer::defaultLayer(int size[2], const byte pixel[])
    {
        auto layer = new Layer();

        layer->setSize(size, pixel);

        return layer;
    }

    Layer *Layer::fromFile(const char *filename)
    {
        auto layer = new Layer();

        layer->m_data = stbi_load(filename, &(layer->m_size[0]), &(layer->m_size[1]), &(layer->m_bpp), 0);

        return layer;
    }

    void Layer::overwrite(Layer *a, Layer *b)
    {
        for (int y = 0; y < b->m_size[1]; y++)
        {
            for (int x = 0; x < b->m_size[0]; x++)
            {
                if (x + a->m_offset[0] < 0)
                {
                    continue;
                }
                if (y + a->m_offset[1] < 0)
                {
                    continue;
                }
                if (x + b->m_offset[0] < 0)
                {
                    continue;
                }
                if (y + b->m_offset[1] < 0)
                {
                    continue;
                }
                if (x + a->m_offset[0] >= a->m_size[0])
                {
                    continue;
                }
                if (y + a->m_offset[1] >= a->m_size[1])
                {
                    continue;
                }
                if (x + b->m_offset[0] >= b->m_size[0])
                {
                    continue;
                }
                if (y + b->m_offset[1] >= b->m_size[1])
                {
                    continue;
                }

                auto bpixel = b->pixel<4>(x + b->m_offset[0], y + b->m_offset[1]);
                if (bpixel[3] == 0)
                {
                    continue;
                }

                a->setPixel<4>(x + a->m_offset[0], y + a->m_offset[1], bpixel);
            }
        }
    }

}