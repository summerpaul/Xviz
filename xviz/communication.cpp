/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 09:42:26
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 11:04:53
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

    Communication::Communication() : m_running(false), m_ctx(), m_sub(m_ctx, zmq::socket_type::sub)
    {
    }
    Communication::~Communication()
    {
        Shutdown();
    }

    bool Communication::Init(const std::string &connect)
    {
        if (m_running)
        {
            return m_running;
        }

        m_sub.connect(connect);
        m_sub.set(zmq::sockopt::rcvtimeo, 100);
        m_sub.set(zmq::sockopt::subscribe, "");
        m_connect = connect;

        m_running = true;

        return true;
    }
    void Communication::Run()
    {
        m_receiveThread = std::thread(&Communication::ReceiveLoop, this);
    }

    void Communication::Shutdown()
    {
        if (m_running)
        {
            m_running = false;
            if (m_receiveThread.joinable())
            {
                m_receiveThread.join();
            }

            m_sub.disconnect(m_connect.c_str());
        }
    }

    void Communication::ReceiveLoop()
    {
        while (m_running)
        {

            zmq::message_t recv_msg;
            zmq::recv_result_t result = m_sub.recv(recv_msg);
            if (recv_msg.size() > 0)
            {
                ParseMessage(recv_msg);
            }
        }
    }

    void Communication::ParseMessage(zmq::message_t &msg)
    {
        Json::Value json_msg;
        Json::Reader reader;
        reader.parse(msg.to_string(), json_msg);
        ParseJsonMsg(json_msg);
    }

    void Communication::ParseJsonMsg(const Json::Value &msg)
    {
        if (msg["paths"].type() != Json::nullValue)
        {
            ParseJsonPathsMsg(msg["paths"]);
        }
    }

    void Communication::ParseJsonPathsMsg(const Json::Value &msg)
    {

        Json::Value::Members members = msg.getMemberNames();
        for (auto iterMember = members.begin(); iterMember != members.end(); iterMember++)
        {
            std::string strKey = *iterMember;
            Json::Value json_path = msg[strKey];

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

            if (json_path["width"].type() != Json::nullValue)
            {
                color_path.width = json_path["width"].asDouble();
            }

            g_sence.AddPath(strKey, color_path);
        }
    }

}