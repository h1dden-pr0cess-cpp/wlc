#ifndef PARSER_HPP
#define PARSER_HPP

#include <protocol/packet.hpp>

#include<vector>
#include<cstdint>

class Parser
{
    public:
        static Packet parser(const std::vector<std::uint8_t>& buf); 
    private:
        static uint16_t read_u16(const std::vector<uint8_t>& buf, uint16_t& value);
        static uint32_t read_u32(const std::vector<uint8_t>& buf, uint32_t& value);

    const std::vector<uint8_t>& pars_buf
};


#endif

