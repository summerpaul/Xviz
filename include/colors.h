/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 17:07:57
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 17:47:49
 */
#include <stdint.h>

#ifndef __COLORS_H__
#define __COLORS_H__
#include "box2d/box2d.h"
namespace xviz
{
    const b2Color WHITE = b2Color(1.0f, 1.0f, 1.0f);
    const b2Color RED = b2Color(1.0f, 0.0f, 0.0f);
    const b2Color GREEN = b2Color(0.0f, 1.0f, 0.0f);
    const b2Color BLUE = b2Color(0.0f, 0.0f, 1.0f);
    const b2Color BLACK = b2Color(0.0f, 0.0f, 0.0f);

} // namespace xviz

#endif /* __COLORS_H__ */
