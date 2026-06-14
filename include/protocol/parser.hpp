#ifndef PARSER_HPP
#define PARSER_HPP

#include <protocol/packet.hpp>

#include <vector>
#include <cstdint>
#include <span>
#include <stdexcept>

class Parser
{
    public:
        static Packet parse(std::span<const uint8_t> buf);
    private:
        static Header parse_header(std::span<const std::uint8_t>& buf);

        static uint16_t read_u16(std::span<const std::uint8_t>& buf);
        static uint32_t read_u32(std::span<const std::uint8_t>& buf); 
};


#endif

