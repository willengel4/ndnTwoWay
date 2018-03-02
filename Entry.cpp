#ifndef ENTRY_H
#define ENTRY_H
#include "Packet.cpp"
#include <vector>
#include "Node.cpp"

using namespace std;

class Entry
{
    public:
        Packet * packet;
        vector<Node*> nodes;
};
#endif