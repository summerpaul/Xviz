/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 00:49:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 01:53:37
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
            DrawGrid();
        }

        DrawOrigin();
    }

    void Sence::DrawGrid()
    {
    }
    void Sence::DrawOrigin()
    {
        b2Vec2 origin(0, 0);
        b2Vec2 x_axis(500, 0);
        b2Vec2 y_axis(0, 500);
        g_debugDraw.DrawSegment(b2Vec2(0, 0), b2Vec2(5.0f, 0), b2Color(0, 1, 0));
        g_debugDraw.DrawSegment(b2Vec2(0, 0), b2Vec2(0, 5.0), b2Color(1, 0, 0));
        g_debugDraw.DrawCircle(b2Vec2(0, 0), 10, b2Color(0, 0, 1));

        // g_debugDraw.DrawSegment()
    }
}