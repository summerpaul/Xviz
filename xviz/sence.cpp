/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 00:49:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 18:53:46
 */
#include <iostream>

#include "sence.h"
#include "colors.h"
namespace xviz
{

    Sence g_sence;

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
    }
    Sence::~Sence()
    {
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

    void Sence::AddPath(const std::string &name, const ColorPath &path)
    {
        m_paths[name] = path;
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

        DrawPaths();
    }

    void Sence::DrawGrid(const Settings &settings)
    {
        for (float x = 0; x <= settings.m_gridWidth; x += settings.m_gridInterval)
        {
            g_debugDraw.DrawSegment(b2Vec2(x, 0), b2Vec2(x, settings.m_gridHeight), WHITE);
        }

        for (float y = 0; y <= settings.m_gridHeight; y += settings.m_gridInterval)
        {
            g_debugDraw.DrawSegment(b2Vec2(0, y), b2Vec2(settings.m_gridWidth, y), WHITE);
        }
    }
    void Sence::DrawOrigin()
    {
        g_debugDraw.DrawSegment(b2Vec2(0, 0), b2Vec2(5.0f, 0), GREEN);
        g_debugDraw.DrawSegment(b2Vec2(0, 0), b2Vec2(0, 5.0), RED);
    }

    void Sence::DrawPaths()
    {
        for (auto &path : m_paths)
        {
            if (path.second.points.size() < 2 || path.second.draw == false)
            {
                return;
            }

            for (int i = 1; i < path.second.points.size(); i++)
            {
                Vector2f p0 = path.second.points[i - 1];
                Vector2f p1 = path.second.points[i];
                g_debugDraw.DrawSegment(b2Vec2(p0.x, p0.y), b2Vec2(p1.x, p1.y), COLOR2b2Color(path.second.color));
            }
        }
    }

    b2Color Sence::COLOR2b2Color(const COLOR &color)
    {
        if (color == COLOR::WHITE)
        {
            return WHITE;
        }
        else if (color == COLOR::BLACK)
        {
            return BLACK;
        }
        else if (color == COLOR::BLUE)
        {
            return BLUE;
        }
        else if (color == COLOR::GREEN)
        {
            return GREEN;
        }
        return WHITE;
    }
}