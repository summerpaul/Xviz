/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 23:22:08
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 15:30:03
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
        m_gridWidth = 20.0f; 
        m_gridHeight = 20.0f;
        m_gridInterval = 1.0;
        m_drawOrigin = true;
        m_drawMousePose = true;
    }

    void Save();
    void Load();
    int m_windowWidth;
    int m_windowHeight;
    float m_hertz;
    bool m_drawGrid;
    int m_gridWidth;
    int m_gridHeight;
    int m_gridInterval;
    bool m_drawOrigin;
    bool m_drawMousePose;
};

#endif /* __SETTINGS_H__ */
