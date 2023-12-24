/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 09:42:26
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 16:06:04
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

            std::vector<zmq::message_t> recv_msgs;
            zmq::recv_result_t result =
                zmq::recv_multipart(m_sub, std::back_inserter(recv_msgs));
            if (recv_msgs.size() > 2)
            {

                if (recv_msgs[0].to_string() == MSG_PATH)
                {
                    ParsePath(recv_msgs[1].to_string(), recv_msgs[2]);
                }
            }
        }
    }
    void Communication::ParsePath(const std::string &name, const zmq::message_t &msg)
    {

        int size = msg.size();
        char buff[size];
        memcpy(buff, msg.data(), size);
        std_msgs::Path2f proto_path;
        proto_path.ParseFromArray(buff, size);

        Path2f path;
        for (auto &proto_pt : proto_path.points())
        {
            Vector2f pt;
            pt.x = proto_pt.x();
            pt.y = proto_pt.y();
            path.emplace_back(pt);
        }

        g_sence.AddPath(name, path);
    }

}