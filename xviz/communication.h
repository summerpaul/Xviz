/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 09:42:11
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 21:00:45
 */
#include <stdint.h>

#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__
#include "zmq.hpp"
#include "zmq_addon.hpp"
#include "sence.h"
#include <future>
#include "json/json.h"
namespace xviz
{

    class Communication
    {
    public:
        bool Init();
        void Run();
        void Connect(const std::string &connect);
        void DisConnect(const std::string &connect);

    private:
        void SubThread();

        void DrawJsonMsg(const Json::Value &msg);
        void DrawJsonPathsMsg(const Json::Value &msg);
        void DrawJsonPathMsg(const Json::Value &json_path);

    private:
        zmq::context_t m_ctx;
        zmq::socket_t m_sub;
        std::future<void> m_subThread;
    };
    extern GLFWwindow *g_mainWindow;
}

#endif /* __COMMUNICATION_H__ */
