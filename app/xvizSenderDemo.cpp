/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 20:20:57
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 15:35:42
 */
#include <iostream>
#include "xvizMsgSender/xvizMsgSender.h"
#include <thread>
#include <chrono>
using namespace std;

int main(int argc, char const *argv[])
{
    xviz::XvizMsgSender sender;

    if (!sender.Init("tcp://127.0.0.1:8888"))
    {
        std::cout << "failed to init " << std::endl;
        return 1;
    }

    xviz::Path2f line_path;
    for (int i = 0; i < 20; i++)
    {
        xviz::Vector2f p;
        p.x = float(i);
        p.y = float(i);
        line_path.emplace_back(p);
    }

    const float k_segments = 120.0f;
    const float k_increment = 2.0f * M_PI / k_segments;

    xviz::Path2f circle_path;
    const float r = 1.0;
    const float origin_x = 1.0;
    const float origin_y = 1.0;
    for (int i = 0; i <= k_segments; i++)
    {
        xviz::Vector2f p;
        p.x = cosf(i * k_increment) + origin_x;
        p.y = sinf(i * k_increment) + origin_y;
        circle_path.emplace_back(p);
    }
    while (true)
    {
        sender.PathPub("line_path",line_path);
        sender.PathPub("circle_path",circle_path);
        std::cout << "send" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "jaja" << std::endl;

    return 0;
}
