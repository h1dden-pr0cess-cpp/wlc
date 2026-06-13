#ifndef PACKET_HPP
#define PACKET_HPP

#include<cstdint>
#include<vector>

enum class MessageType : uint16_t
{
    Discovery,
    DiscoveryResponse,
    JoinRequest,
    JoinResponse,
    EchoRequest,
    EchoResponse,
    KeepAlive,
    Config,
    Ack,
    Error
};

struct Header
{
    uint32_t magic;          // WLC1
    uint16_t version;        // 1
    MessageType type;        // enum
    uint32_t session_id;     // AP session context
    uint32_t request_id;     // correlation
    uint32_t sequence;       // ordering / retry tracking
    uint32_t payload_length; // body size

    uint16_t flags;          // future behavior control
    uint16_t reserved;       // alignment + future use
};
struct Packet
{
    Header header;

    std::vector<std::uint8_t> payload;
};

#endif 
