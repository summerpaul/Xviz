/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-23 19:43:35
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-24 15:47:04
 */
#include <stdint.h>

#ifndef __XVIZMSGSENDER_H__
#define __XVIZMSGSENDER_H__
#include "zmq.hpp"
#include "zmq_addon.hpp"
#include "dataTypes.h"
#include "protoMessage/pb/std_msgs.pb.h"
#include "protoMessage/pb/sensor_msgs.pb.h"

#include <mutex>

namespace xviz
{
    class XvizMsgSender
    {
    public:
        XvizMsgSender();
        ~XvizMsgSender();
        bool Init(const std::string connect);
        void PathPub(const std::string &topic, const Path2f &path);
        void Shutdown();

    private:
        template <typename PROTO_MSG>
        void PubProto(const PROTO_MSG &proto_msg,
                      const std::string &topic, const std::string &msg_type);

    private:
        zmq::context_t m_ctx;
        zmq::socket_t m_pub;
        std::string m_connect;
        bool m_running;

        std::mutex m_mtx;
    };

} // namespace xviz

#endif /* __XVIZMSGSENDER_H__ */
