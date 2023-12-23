/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 09:42:26
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 21:24:02
 */
#include <iostream>
#include "communication.h"
#include <thread>
#include <chrono>
#include "sence.h"
#include "dataTypes.h"
using namespace std;
namespace xviz
{

    bool Communication::Init()
    {

        m_sub = zmq::socket_t(m_ctx, zmq::socket_type::sub);

        return true;
    }
    void Communication::Run()
    {
        m_subThread =
            std::async(std::launch::async, &Communication::SubThread, this);
    }

    void Communication::Connect(const std::string &connect)
    {
        m_sub.connect(connect);
        m_sub.set(zmq::sockopt::subscribe, "");
    }

    void Communication::DisConnect(const std::string &connect)
    {

        if (m_sub.connected())
        {
            m_sub.disconnect(connect);
        }
    }

    void Communication::SubThread()
    {
        std::cout << "start SubThread " << std::endl;
        while (!glfwWindowShouldClose(g_mainWindow))
        {

            std::vector<zmq::message_t> recv_msgs;
            zmq::recv_result_t result =
                zmq::recv_multipart(m_sub, std::back_inserter(recv_msgs), zmq::recv_flags::dontwait);
            if (*result == 0)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(100));
            }
            else
            {

                Json::Value json_msg;
                Json::Reader reader;
                if (!reader.parse(recv_msgs[0].to_string(), json_msg))
                {
                    std::cout << "failed to load config file " << std::endl;
                    return;
                }
                else
                {
                    DrawJsonMsg(json_msg);

                    //  std::cout << "haha" << std::endl;
                }
            }
        }
    }

    void Communication::DrawJsonMsg(const Json::Value &msg)
    {
        std::cout << " json msg is " << msg << std::endl;
        if (msg["paths"].type() != Json::nullValue)
        {
            std::cout << "draw paths" << std::endl;
            DrawJsonPathsMsg(msg["paths"]);
        }
    }

    void Communication::DrawJsonPathsMsg(const Json::Value &msg)
    {
        for (auto &jsonPathMsg : msg)
        {

            DrawJsonPathMsg(jsonPathMsg);
        }
    }
    void Communication::DrawJsonPathMsg(const Json::Value &json_path)
    {
        std::cout << "json_path is " << json_path << std::endl;
        ColorPath color_path;
        if (json_path["color"].type() != Json::nullValue)
        {
            color_path.color = COLOR(json_path["color"].asInt());
        }

        if (json_path["points"].type() != Json::nullValue)
        {

            for (auto &json_pt : json_path["points"])
            {
                Vector2f pt;
                pt.x = json_pt["x"].asDouble();
                pt.y = json_pt["y"].asDouble();
                color_path.points.emplace_back(pt);
            }
        }
    }
}