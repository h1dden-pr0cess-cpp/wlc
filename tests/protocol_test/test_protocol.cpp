#include "protocol/packet.hpp"
#include "protocol/parser.hpp"
#include "protocol/serializer.hpp"

#include <cassert>
#include <iostream>

void test_basic_packet()
{
    Packet p{};

    p.header.magic = MAGIC;
    p.header.version = VERSION;
    p.header.type = MessageType::Discovery;

    p.header.session_id = 123;
    p.header.request_id = 456;
    p.header.sequence = 789;

    p.header.flags = 0;
    p.header.reserved = 0;

    p.payload = {1,2,3,4,5,6,7,8};

    p.header.payload_length =
        static_cast<uint32_t>(p.payload.size());

    // serialize
    auto bytes = Serializer::serialize(p);

    // parse back
    Packet out = Parser::parse(bytes);

    // checks
    assert(p.header.magic == out.header.magic);
    assert(p.header.version == out.header.version);
    assert(p.header.type == out.header.type);

    assert(p.header.session_id == out.header.session_id);
    assert(p.header.request_id == out.header.request_id);
    assert(p.header.sequence == out.header.sequence);

    assert(p.header.payload_length == out.header.payload_length);

    assert(p.header.flags == out.header.flags);
    assert(p.header.reserved == out.header.reserved);

    assert(p.payload == out.payload);

    std::cout << "✔ test_basic_packet PASSED\n";
}

int main()
{
    test_basic_packet();
    return 0;
}
