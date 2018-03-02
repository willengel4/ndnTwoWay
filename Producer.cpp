#ifndef PRODUCER_H
#define PRODUCER_H
#include <string>
#include "Packet.cpp"
#include "Node.cpp"

using namespace std;

class Producer : public Node
{
    public:
        string prefix;

        virtual void Act()
        {
            Node::Act();

            string newDataName = prefix + GenerateName(10);
            int newDataSize = rand() % 100 + 10;
            Packet * p = new Packet(0, newDataSize, newDataName);
            contentStore.AddEntry(p, NULL);
        }

        string GenerateName(int len)
        {
            string s = "";

            for(int i = 0; i < len; i++)
                s += (char)(rand() % 74 + 38);

            return s;
        }
};
#endif