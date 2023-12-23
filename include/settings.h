/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 23:22:08
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 09:51:21
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
        m_gridWidth = 10.0f; 
        m_gridHeight = 10.0f;
        m_gridInterval = 1.0;
    }

    void Save();
    void Load();
    int m_windowWidth;
    int m_windowHeight;
    float m_hertz;
    bool m_drawGrid;
    float m_gridWidth;
    float m_gridHeight;
    float m_gridInterval;
};

#endif /* __SETTINGS_H__ */
