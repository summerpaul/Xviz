/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 00:49:10
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 16:51:37
 */
#include <stdint.h>

#ifndef __SENCE_H__
#define __SENCE_H__
#include "box2d/box2d.h"
#include "draw.h"

#include "settings.h"
#include "dataTypes.h"
#include <unordered_map>
#include <string>
namespace xviz
{

    struct DrawPath
    {
        Path2f path;
        bool draw = true;
        int color = 0;
        float width = 0.05;
    };

    class Sence
    {

    public:
        Sence();
        ~Sence();

        void Keyboard(int key) { B2_NOT_USED(key); }
        void KeyboardUp(int key) { B2_NOT_USED(key); }
        void ShiftMouseDown(const b2Vec2 &p);
        void MouseDown(const b2Vec2 &p);
        void MouseUp(const b2Vec2 &p);
        void MouseMove(const b2Vec2 &p);

        void Draw(const Settings &settings);

        void AddPath(const std::string &name, const Path2f &path);

    private:
        void DrawOrigin();

        void DrawGrid(const Settings &settings);

        void DrawPaths();

        b2Color Int2b2Color(const int &color);

    public:
        b2Vec2 m_mousePose;

        std::unordered_map<std::string, DrawPath> m_paths;

    };

    extern Sence g_sence;

}

#endif /* __SENCE_H__ */
