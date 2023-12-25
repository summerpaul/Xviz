/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 19:44:45
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-25 10:20:14
 */
#include <iostream>
#include "xvizMsgSender.h"
using namespace std;
namespace xviz
{

    XvizMsgSender::XvizMsgSender()
        : m_running(false), m_ctx(), m_pub(m_ctx, zmq::socket_type::pub)
    {
    }
    XvizMsgSender::~XvizMsgSender()
    {
        Shutdown();
    }
    bool XvizMsgSender::Init(const std::string connect)
    {

        if (m_running)
        {
            return m_running;
        }
        m_connect = connect;
        try
        {
            m_pub.bind(connect);
        }
        catch (const std::exception &e)
        {
            m_pub.connect(connect);
            std::cerr << e.what() << '\n';
            return false;
        }
        m_running = true;
        return true;
    }

    void XvizMsgSender::PathPub(const std::string &topic, const Path2f &path)
    {
        std_msgs::Path2f proto_path;
        for (auto &pt : path)
        {
            std_msgs::Vector2f *new_point = proto_path.add_points();
            new_point->set_x(pt.x);
            new_point->set_y(pt.y);
        }

        PubProto(proto_path, topic, MSG_PATH);
    }

    template <typename PROTO_MSG>
    void XvizMsgSender::PubProto(const PROTO_MSG &proto_msg,
                                 const std::string &topic, const std::string &msg_type)
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        zmq::message_t target_msg;
        std::string string_msg;
        proto_msg.SerializeToString(&string_msg);
        target_msg.rebuild(string_msg);
        m_pub.send(zmq::message_t(std::string(msg_type)), zmq::send_flags::sndmore);
        m_pub.send(zmq::message_t(std::string(topic)), zmq::send_flags::sndmore);
        m_pub.send(target_msg);
    }

    void XvizMsgSender::Shutdown()
    {

        if (m_pub.connected())
        {
            m_pub.disconnect(m_connect.c_str());
        }

        m_running = false;
    }
}