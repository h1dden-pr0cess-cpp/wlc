#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <protocol/packet.hpp>

#include<vector>
#include<cstdint>

constexpr std::size_t HEADER_SIZE =
    sizeof(std::uint32_t) + // magic
    sizeof(std::uint16_t) + // version
    sizeof(std::uint16_t) + // type
    sizeof(std::uint32_t) + // session_id
    sizeof(std::uint32_t) + // request_id
    sizeof(std::uint32_t) + // sequence
    sizeof(std::uint32_t) + // payload_length
    sizeof(std::uint16_t) + // flags
    sizeof(std::uint16_t);  // reserved


class Serializer
{
public:
    static std::vector<std::uint8_t> serialize(const Packet& p);

private:
    static void write_u16(std::vector<uint8_t>& buf, uint16_t value);
    static void write_u32(std::vector<uint8_t>& buf, uint32_t value);

};

#endif
