#include "protocol/parser.hpp"

Packet Parser::parse(std::span<const std::uint8_t> buf)
{
    Packet packet{};

    packet.header = parse_header(buf);

    if (buf.size() < packet.header.payload_length)
    {
        throw std::runtime_error("Invalid payload length");
    }

    packet.payload.assign(
        buf.begin(),
        buf.begin() + packet.header.payload_length
    );

    buf = buf.subspan(packet.header.payload_length);

    if (!buf.empty())
    {
        //extra data
    }

    return packet;
}


Header Parser::parse_header(std::span<const std::uint8_t>& buf)
{
    Header header{};

    header.magic = read_u32(buf);

    if (header.magic != MAGIC)
    {
        throw std::runtime_error("Invalid magic");
    }

    header.version = read_u16(buf);

    if (header.version != VERSION)
    {
        throw std::runtime_error("Unsupported protocol version");
    }

    header.type = static_cast<MessageType>(read_u16(buf));

    header.session_id     = read_u32(buf);
    header.request_id     = read_u32(buf);
    header.sequence       = read_u32(buf);
    header.payload_length = read_u32(buf);

    header.flags    = read_u16(buf);
    header.reserved = read_u16(buf);

    return header;
}


uint16_t Parser::read_u16(std::span<const std::uint8_t>& buf)
{
    if(buf.size() < 2) 
        throw std::runtime_error("Buffer underflow");

    uint16_t value =
    (static_cast<uint16_t>(buf[0]) << 8) |
     static_cast<uint16_t>(buf[1]);

    buf = buf.subspan(2);

    return value;
}
uint32_t Parser::read_u32(std::span<const std::uint8_t>& buf)
{
    if(buf.size() < 4) 
        throw std::runtime_error("Buffer underflow");


    uint32_t value =
    (static_cast<uint32_t>(buf[0]) << 24) |
    (static_cast<uint32_t>(buf[1]) << 16) |
    (static_cast<uint32_t>(buf[2]) << 8 ) |
     static_cast<uint32_t>(buf[3]);

    buf = buf.subspan(4);

    return value;
}
