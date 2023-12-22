/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 23:22:24
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 00:06:47
 */
#include <iostream>
#include "settings.h"
#include <fstream>
#include "json/json.h"
using namespace std;

static const char *fileName = "settings.ini";

void Settings::Save()
{

    Json::StyledWriter write;
    Json::Value json_cfg;
    json_cfg["windowHeight"] = m_windowHeight;
    json_cfg["windowWidth"] = m_windowWidth;
    json_cfg["hertz"] = m_hertz;

    std::string out = write.write(json_cfg);
    std::ofstream os(fileName);
    os << out;
    os.close();
    printf("save settings \n");
}
void Settings::Load()
{

    std::ifstream ifs(fileName); // open file example.json
    Json::Value json_cfg;
    Json::Reader reader;
    if (!reader.parse(ifs, json_cfg))
    {
        std::cout << "failed to load config file " << std::endl;
        return;
    }

    if (json_cfg["hertz"].type() != Json::nullValue)
    {
        m_hertz = json_cfg["hertz"].asDouble();
        printf("load hertz\n");
    }

    if (json_cfg["windowHeight"].type() != Json::nullValue)
    {
        m_windowHeight = json_cfg["windowHeight"].asInt();
        printf("load windowHeight\n");
    }

    if (json_cfg["windowWidth"].type() != Json::nullValue)
    {
        m_windowWidth = json_cfg["windowWidth"].asInt();
        printf("load windowHeight\n");
    }
}