/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 16:47:32
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-25 09:07:52
 */
#include <stdint.h>

#ifndef __DATATYPES_H__
#define __DATATYPES_H__
#include <vector>
namespace xviz
{

    enum class COLOR
    {
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE

    };

    struct Pose
    {
        float x;
        float y;
        float theta;
    };

    struct Vector2f
    {
        float x;
        float y;
    };

    struct Vector2i
    {
        int x;
        int y;
    };

    struct PointCloud2f
    {
        double time;
        std::vector<Vector2f> points;
    };

    typedef std::vector<Vector2f> Path2f;
    typedef std::vector<Vector2i> Path2i;

    const std::string MSG_PATH = "MSG_PATH";

} // namespace xviz

#endif /* __DATATYPES_H__ */
