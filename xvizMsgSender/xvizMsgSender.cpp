/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 19:44:45
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 00:47:34
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
    void XvizMsgSender::AddPath(const std::string &name, const ColorPath &path)
    {
        std::cout << "start add path " << std::endl;
        Json::Value colorPath;
        colorPath["color"] = int(path.color);
        for (auto &pt : path.points)
        {
            Json::Value json_pt;
            json_pt["x"] = pt.x;
            json_pt["y"] = pt.y;
            colorPath["points"].append(json_pt);
        }
        m_jsonPathMsg[name] = colorPath;
    }

    void XvizMsgSender::Send()
    {
        m_jsonMsg["paths"] = m_jsonPathMsg;
        std::string send_str = m_jsonMsg.toStyledString();
        m_pub.send(zmq::message_t(send_str), zmq::send_flags::dontwait);
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