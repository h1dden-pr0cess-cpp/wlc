#include"protocol/serializer.hpp"


void Serializer::write_u16(std::vector<uint8_t>& buf, uint16_t value)
{
    buf.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
    buf.push_back(static_cast<uint8_t>( value       & 0xFF));
}

void Serializer::write_u32(std::vector<uint8_t>& buf, uint32_t value)
{
    buf.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
    buf.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
    buf.push_back(static_cast<uint8_t>((value >> 8)  & 0xFF));
    buf.push_back(static_cast<uint8_t>( value        & 0xFF));
}
std::vector<std::uint8_t> Serializer::serialize(const Packet& p)
{
    std::vector<std::uint8_t> ret;
    ret.reserve(HEADER_SIZE + p.payload.size());

    write_u32(ret, p.header.magic);
    write_u16(ret, p.header.version);

    write_u16(ret, static_cast<std::uint16_t>(p.header.type));

    write_u32(ret, p.header.session_id);
    write_u32(ret, p.header.request_id);
    write_u32(ret, p.header.sequence);
    write_u32(ret, static_cast<std::uint32_t>(p.payload.size()));
    write_u16(ret, p.header.flags);
    write_u16(ret, p.header.reserved);

    for(uint8_t temp : p.payload)
    {
        ret.push_back(temp);
    }
    return ret;
}
