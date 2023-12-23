/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 00:49:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 15:50:13
 */
#include <iostream>

#include "sence.h"

namespace xviz
{

    namespace
    {
        std::string doubleToString(const double &val)
        {
            char *chCode;
            chCode = new char[20];
            sprintf(chCode, "%.2lf", val);
            std::string str(chCode);
            delete[] chCode;
            return str;
        }

    }

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

    void Sence::ShiftMouseDown(const b2Vec2 &p)
    {
    }
    void Sence::MouseDown(const b2Vec2 &p)
    {
    }
    void Sence::MouseUp(const b2Vec2 &p)
    {
    }
    void Sence::MouseMove(const b2Vec2 &p)
    {
        m_mousePose = p;
    }

    void Sence::Draw(const Settings &settings)
    {

        g_debugDraw.Flush();
        if (settings.m_drawGrid)
        {
            DrawGrid(settings);
        }

        if (settings.m_drawOrigin)
        {
            DrawOrigin();
        }
        if (settings.m_drawMousePose)
        {

            std::string mouse_pose_str = "[" + doubleToString(m_mousePose.x) + ", " + doubleToString(m_mousePose.y) + "]";
            g_debugDraw.DrawString(m_mousePose, mouse_pose_str.data());
        }
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
    }
}