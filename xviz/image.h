/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-24 21:19:33
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 22:07:39
 */
#ifndef IMAGE_H
#define IMAGE_H

#include "layer.h"
#include <string>
#include <vector>

namespace xviz
{
    class Image
    {
    public:
        Image();
        Image(const char *name);
        virtual ~Image();

        std::vector<Layer *> m_layers;
        std::string m_name;
        int m_flags = 0;
        std::string m_fullPath;
        int m_size[2] = {256, 256};

        Layer *addLayer();
        void fromFile(const char *filename);
        bool isDirty() const;
        void setDirty() { m_flags |= Dirty; }
        void selectLayer(size_t index);
        void removeCurrentLayer();
        void moveCurrentLayerUp();
        void moveCurrentLayerDown();

        unsigned char *m_data = nullptr;

        size_t m_selectedLayer = 0;
    };
}

#endif // IMAGE_H
