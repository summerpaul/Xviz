/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 20:20:57
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 00:47:51
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

    xviz::ColorPath path;
    path.color = xviz::COLOR::GREEN;
    for (int i = 0; i < 20; i++)
    {
        xviz::Vector2f p;
        p.x = float(i);
        p.y = float(i);
        path.points.emplace_back(p);
    }
    sender.AddPath("sender_test", path);
    std::cout << "add path" << std::endl;
    while (true)
    {
        sender.Send();
        std::cout << "send" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "jaja" << std::endl;

    return 0;
}
