/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-24 21:19:33
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 21:27:33
 */
#include "image.h"
#include "stb_image.h"

namespace xviz
{
    Image::Image() = default;

    Image::~Image()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
            m_data = nullptr;
        }
    }

    Layer *Image::addLayer()
    {
        byte pixel[4] = {255, 255, 255, 255};
        auto layer = Layer::defaultLayer(this->m_size, pixel);
        layer->m_name = std::string("Layer ") + std::to_string(this->m_layers.size() + 1);
        layer->setDirty();
        this->m_layers.push_back(layer);

        return layer;
    }

    void Image::fromFile(const char *filename)
    {
        auto layer = Layer::fromFile(filename);
        layer->m_name = std::string("Layer ") + std::to_string(this->m_layers.size());
        layer->setDirty();
        this->m_size[0] = layer->m_size[0];
        this->m_size[1] = layer->m_size[1];
        this->m_layers.push_back(layer);
    }

    void Image::selectLayer(size_t index)
    {
        if (index >= 0 && index < this->m_layers.size())
        {
            m_selectedLayer = index;
        }
    }

    bool Image::isDirty() const
    {
        if (m_flags & Dirty)
        {
            return true;
        }

        for (Layer *layer : this->m_layers)
        {
            if (layer->m_flags & Dirty)
            {
                return true;
            }
        }

        return false;
    }

    void Image::removeCurrentLayer()
    {
        if (this->m_layers.size() > 1)
        {
            this->m_layers.erase(this->m_layers.begin() + this->m_selectedLayer);
            if (this->m_selectedLayer > 0)
            {
                this->m_selectedLayer--;
            }

            this->setDirty();
        }
    }

    void Image::moveCurrentLayerUp()
    {
        if (this->m_selectedLayer >= 1)
        {
            auto tmp = this->m_layers[this->m_selectedLayer];
            this->m_layers[this->m_selectedLayer] = this->m_layers[this->m_selectedLayer - 1];
            this->m_layers[this->m_selectedLayer - 1] = tmp;
            this->m_selectedLayer--;
            this->setDirty();
        }
    }

    void Image::moveCurrentLayerDown()
    {
        if (this->m_selectedLayer < this->m_layers.size() - 1)
        {
            auto tmp = this->m_layers[this->m_selectedLayer];
            this->m_layers[this->m_selectedLayer] = this->m_layers[this->m_selectedLayer + 1];
            this->m_layers[this->m_selectedLayer + 1] = tmp;
            this->m_selectedLayer++;
            this->setDirty();
        }
    }

}
