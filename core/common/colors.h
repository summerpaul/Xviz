/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 17:07:57
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-25 23:21:07
 */
#include <stdint.h>

#ifndef __COLORS_H__
#define __COLORS_H__
#include "box2d/box2d.h"
namespace xviz
{
    const b2Color B2WHITE = b2Color(1.0f, 1.0f, 1.0f);
    const b2Color B2RED = b2Color(1.0f, 0.0f, 0.0f);
    const b2Color B2GREEN = b2Color(0.0f, 1.0f, 0.0f);
    const b2Color B2BLUE = b2Color(0.0f, 0.0f, 1.0f);
    const b2Color B2BLACK = b2Color(0.0f, 0.0f, 0.0f);

} // namespace xviz

#endif /* __COLORS_H__ */
