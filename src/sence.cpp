/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 00:49:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 09:58:10
 */
#include <iostream>

#include "sence.h"

namespace xviz
{

    Sence::Sence()
    {
        b2Vec2 gravity;
        gravity.Set(0.0f, 0.0f);
        m_world = new b2World(gravity);
    }
    Sence::~Sence()
    {
        delete m_world;
        m_world = NULL;
    }

    void Sence::Draw(const Settings &settings)
    {

        g_debugDraw.Flush();
        if (settings.m_drawGrid)
        {
            DrawGrid(settings);
        }

        DrawOrigin();
    }

    void Sence::DrawGrid(const Settings &settings)
    {
        for (float x = 0; x <= settings.m_gridWidth; x += settings.m_gridInterval)
        {
            g_debugDraw.DrawSegment(b2Vec2(x, 0), b2Vec2(x, settings.m_gridHeight), b2Color(1, 1, 1));
        }

        for (float y = 0; y <= settings.m_gridHeight; y += settings.m_gridInterval)
        {
            g_debugDraw.DrawSegment(b2Vec2(0, y), b2Vec2(settings.m_gridWidth, y), b2Color(1, 1, 1));
        }
    }
    void Sence::DrawOrigin()
    {
        g_debugDraw.DrawSegment(b2Vec2(0, 0), b2Vec2(5.0f, 0), b2Color(0, 1, 0));
        g_debugDraw.DrawSegment(b2Vec2(0, 0), b2Vec2(0, 5.0), b2Color(1, 0, 0));
        g_debugDraw.DrawCircle(b2Vec2(0, 0), 10, b2Color(0, 0, 1));

        // g_debugDraw.DrawSegment()
    }
}