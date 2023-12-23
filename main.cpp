/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 18:14:46
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 19:42:42
 */
#include <iostream>
#include "xviz/xviz.h"
#include "logger.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    XLogger::getInstance()->init("log","xviz","info",true);
    xviz::Xviz::Ptr viz;
    viz.reset(new xviz::Xviz);

    if (!viz->Init())
    {
        return 1;
    }
    viz->Run();

    return 0;
}
