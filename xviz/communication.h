/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 09:42:11
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 15:58:20
 */
#include <stdint.h>

#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__
#include "zmq.hpp"
#include "zmq_addon.hpp"
#include "sence.h"
#include <future>
#include "protoMessage/pb/std_msgs.pb.h"
#include "protoMessage/pb/sensor_msgs.pb.h"
namespace xviz
{

    class Communication
    {
    public:
        Communication();
        ~Communication();
        bool Init(const std::string &connect);
        void Run();
        void Shutdown();

    private:
        void ReceiveLoop();

        void ParsePath(const std::string &name, const zmq::message_t &msg);

    private:
        zmq::context_t m_ctx;
        zmq::socket_t m_sub;
        std::thread m_receiveThread;
        std::string m_connect;
        bool m_running;
    };
    extern GLFWwindow *g_mainWindow;
}

#endif /* __COMMUNICATION_H__ */
