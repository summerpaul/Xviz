/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 23:22:24
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 19:27:43
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
    json_cfg["drawGrid"] = m_drawGrid;
    json_cfg["drawMousePose"] = m_drawMousePose;
    json_cfg["drawOrigin"] = m_drawOrigin;
    json_cfg["gridHeight"] = m_gridHeight;
    json_cfg["gridInterval"] = m_gridInterval;
    json_cfg["gridWidth"] = m_gridWidth;
    json_cfg["subConnect"] = m_subConnect;

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
    }

    if (json_cfg["drawGrid"].type() != Json::nullValue)
    {
        m_drawGrid = json_cfg["drawGrid"].asBool();
    }

    if (json_cfg["drawOrigin"].type() != Json::nullValue)
    {
        m_drawOrigin = json_cfg["drawOrigin"].asBool();
    }

    if (json_cfg["drawMousePose"].type() != Json::nullValue)
    {
        m_drawMousePose = json_cfg["drawMousePose"].asBool();
    }

    if (json_cfg["gridHeight"].type() != Json::nullValue)
    {
        m_gridHeight = json_cfg["gridHeight"].asInt();
    }

    if (json_cfg["gridWidth"].type() != Json::nullValue)
    {
        m_gridWidth = json_cfg["gridWidth"].asInt();
    }

    if (json_cfg["gridInterval"].type() != Json::nullValue)
    {
        m_gridInterval = json_cfg["gridInterval"].asInt();
    }


     if (json_cfg["subConnect"].type() != Json::nullValue)
    {
        m_subConnect = json_cfg["subConnect"].asString();
    }
}