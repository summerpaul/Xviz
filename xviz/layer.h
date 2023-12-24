/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-24 21:19:33
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 22:39:15
 */
#ifndef LAYER_H
#define LAYER_H

#include <string>

namespace xviz
{
    enum eFlags
    {
        Dirty = 1 << 0,
    };

    typedef unsigned char byte;

    class Layer
    {
    public:
        Layer();

        std::string m_name;
        int m_flags = 0;
        bool m_visible = true;
        bool isVisible() const { return m_visible; }
        void toggleVisibility()
        {
            m_visible = !m_visible;
            setDirty();
        }
        void setDirty() { m_flags |= Dirty; }
        int dataSize() const;
        void setSize(int size[2]);
        void setSize(int w, int h);
        void setSize(int size[2], const byte pixel[]);
        void setSize(int w, int h, const byte pixel[]);
        template <int N>
        const byte *pixel(int x, int y) const
        {
            int position = y * m_size[1] + x;
            return &this->m_data[position * N];
        }
        template <int N>
        void setPixel(int x, int y, const byte pixel[])
        {
            int position = y * m_size[1] + x;
            for (int b = 0; b < N; b++)
            {
                this->m_data[position * N + b] = pixel[b];
            }
        }

        float m_alpha = 1.0f;
        int m_alphaMode = 0;

        int m_offset[2] = {0, 0};
        int m_size[2] = {0, 0};
        int m_bpp = 4;
        unsigned char *m_data = nullptr;

        static Layer *defaultLayer(int size[2], const byte pixel[]);
        static Layer *fromFile(const char *filename);
        static void overwrite(Layer *a, Layer *b);
    };

}

#endif // LAYER_H
