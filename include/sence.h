/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 00:49:10
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 01:36:18
 */
#include <stdint.h>

#ifndef __SENCE_H__
#define __SENCE_H__
#include "box2d/box2d.h"
#include "draw.h"

#include "settings.h"
namespace xviz

{
    class Sence
    {

    public:
        Sence();
        ~Sence();

        void Draw(const Settings& settings);

    private:
        void DrawOrigin();

        void DrawGrid();

    private:
        b2World *m_world;
    };

}

#endif /* __SENCE_H__ */
