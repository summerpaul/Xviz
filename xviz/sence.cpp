/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 00:49:25
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 11:29:03
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
        if (m_pathsDraw.count(name) == 0)
        {
            std::cout << "add draw_flag" << std::endl;
            m_pathsDraw[name] = true;
        }
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
            // g_debugDraw.DrawString(m_mousePose, "lll");
        }

        DrawPaths();
    }

    void Sence::DrawGrid(const Settings &settings)
    {
        for (float x = 0; x <= settings.m_gridWidth; x += settings.m_gridInterval)
        {
            g_debugDraw.DrawSegment(b2Vec2(x, 0), b2Vec2(x, settings.m_gridHeight), WHITE, 0.05);
        }

        for (float y = 0; y <= settings.m_gridHeight; y += settings.m_gridInterval)
        {
            g_debugDraw.DrawSegment(b2Vec2(0, y), b2Vec2(settings.m_gridWidth, y), WHITE, 0.05);
        }
    }
    void Sence::DrawOrigin()
    {
        g_debugDraw.DrawSegment(b2Vec2(0, 0), b2Vec2(5.0f, 0), GREEN, 0.05);
        g_debugDraw.DrawSegment(b2Vec2(0, 0), b2Vec2(0, 5.0), RED, 0.05);
    }

    void Sence::DrawPaths()
    {
        for (auto &path : m_paths)
        {

            if (path.second.points.size() < 2 || m_pathsDraw[path.first] == false)
            {
                continue;
            }

            for (int i = 1; i < path.second.points.size(); i++)
            {
                Vector2f p0 = path.second.points[i - 1];
                Vector2f p1 = path.second.points[i];
                g_debugDraw.DrawSegment(b2Vec2(p0.x, p0.y), b2Vec2(p1.x, p1.y), COLOR2b2Color(path.second.color), path.second.width);
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
        else if (color == COLOR::RED){
            return RED;
        }
        return WHITE;
    }
}