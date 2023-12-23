/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 19:43:35
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-23 21:18:22
 */
#include <stdint.h>

#ifndef __XVIZMSGSENDER_H__
#define __XVIZMSGSENDER_H__
#include "zmq.hpp"
#include "zmq_addon.hpp"
#include "json/json.h"
#include "dataTypes.h"
namespace xviz
{
    class XvizMsgSender
    {
    public:
        ~XvizMsgSender();
        bool Init(const std::string connect);
        void AddPath(const std::string &name, const ColorPath &path);
        void Send();
        void Disconnect();

    private:
        Json::Value m_jsonMsg;
        Json::Value m_jsonPathMsg;
        zmq::context_t m_ctx;
        zmq::socket_t m_pub;
        std::string m_connect;
    };

} // namespace xviz

#endif /* __XVIZMSGSENDER_H__ */
