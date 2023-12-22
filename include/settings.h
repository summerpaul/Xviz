/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 23:22:08
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 01:35:38
 */
#include <stdint.h>

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

struct Settings
{
    Settings()
    {
        Reset();
    }
    void Reset()
    {
        m_windowWidth = 1600;
        m_windowHeight = 900;
        m_hertz = 60.0f;
        m_drawGrid = true;
    }

    void Save();
    void Load();
    int m_windowWidth;
    int m_windowHeight;
    float m_hertz;
    bool m_drawGrid;
};

#endif /* __SETTINGS_H__ */
