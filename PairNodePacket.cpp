#ifndef PAIRNODEPACKET_H
#define PAIRNODEPACKET_H
#include "Packet.cpp"
#include "Node.cpp"

using namespace std;

class PairNodePacket
{
    public:
        Node * node;
        Packet * packet;

        PairNodePacket(Node * n, Packet * p)
        {
            node = n;
            packet = p;
        }
};
#endif